/**
 * GameScene.cpp
 * Defines the GameScene class.
 */

#include "GameScene.h"
#include "Block.h"
#include "Coin.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include <irrKlang.h>
#include "MenuScene.h"
#include <algorithm>
#include "EndGameScene.h"
#include "GameOverScene.h"
#include "GameHUD.h"
#include "fileutil.h"
#include "Highscore.h"

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {

}


GameScene::~GameScene() {
    if (level_)
        unload_level();

}

void GameScene::start() {
    score_ = 0;
    levelScore_ = 0;
    lives_ = 3;

    /* Load first level. */
    load_level("lvl/level01.dat");

    /* Load commands. */
    GameScene * const gameScene = this;
    window()->console()->register_command("startlevel", 
        [gameScene](Console * const console, const char * args) -> bool {

        if (!strlen(args)) {
            console->log_notice("Usage: startlevel [path]");
            return true;
        }

        if (!has_extension(args, ".dat")) {
            console->log_error("Given path is not a .dat file.");
            console->log_notice("Usage: startlevel [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist");
            console->log_notice("Usage: startlevel [path]");
            return true;
        }

        if (gameScene->level())
            gameScene->unload_level();

        console->log_notice("Loading level from %s.", args);
        gameScene->load_level(args);
        return true;
    });
}

void GameScene::load_level(const char * path) {
    if (level_) {
        window()->console()->log_error("Can't load level %s.", path);
        window()->console()->log_error("A level has already been loaded!");
        return;
    }

    window()->console()->log_notice("Loading level %s.", path);
    strcpy_s(lastLevelPath_, path);

    level_ = LevelManager::load(path, this, player_);

    state(PLAYING);
    hud_.push_back(dialog_ = new DialogHUD(player_, this));
    hud_.push_back(new GameHUD());


    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;

    for (auto object : *level_->playable_layer()) {
        minX = min(minX, (int)object->position().x);
        maxX = max(maxX, (int)object->position().x);
        minY = min(minY, (int)object->position().y);
        maxY = max(maxY, (int)object->position().y);
    }

    int boxX = (minX + maxX) / 2;
    int boxY = (minY + maxY) / 2;

    quadTree_ = new QuadTree(AABB(Vector2(boxX, boxY), 
        Vector2(maxX - minX + 100, maxY - minY + 100)));

    /* Add every object in the playable layer to the quadtree */
    for (auto object : *level_->playable_layer()) {
        if (object == NULL || object == player())
            continue;

        quadTree_->insert_object(object);
    }

    sound_engine()->stopAllSounds();

    if (strlen(level_->sound())) {
        window()->console()->log_notice("Playing level sound %s.", level_->sound());
        sound_engine()->play2D(level_->sound(), true);
    }
}

void GameScene::unload_level() {
    if (!level_) {
        window()->console()->log_error("Can't unload level.");
        window()->console()->log_error("No level is currently loaded!");
        return;
    }

    delete level_;
    delete quadTree_;

    for (auto hud : hud_)
        delete hud;
    hud_.clear();
    dialog_ = NULL;

    level_ = NULL;
}

void GameScene::add_score(int score) {
    levelScore_ += score;
}

void GameScene::update(double delta, Keys keys) {
    if (!level_) {
        return;
    }

	update_viewport();
	check_states();

    /* No matter the state of the scene update the HUD. */
    for (auto hud : hud_) {
        hud->update(this, delta, keys);
    }

	switch (state_)
	{
	case PAUSED:
		return;
	case TALKING:
		return;
    case PLAYER_DEAD: {
        lives_--;

        window()->console()
            ->log_notice("Updated lives to %d.", lives_);

        if (lives_ > 0) {
            window()->console()
                ->log_notice("Reloading with %d lives.", lives_);
            unload_level();
            load_level(lastLevelPath_);
            sound_engine()->play2D("snd/smb_mariodie.wav");
            levelScore_ = 0;
        }
        else
        {
            window()->console()
                ->log_notice("No lives left. "
                "Changing to game over scene.");
            window_->change_scene(new GameOverScene(window_));
            
        }
        return;
    }
    case REACHED_END:
        window()->console()->log_notice("Player reached end. (%f, %f)", 
            player()->position().x, player()->position().y);

        score_ += levelScore_;
        levelScore_ = 0;

        if (level_->is_last_level()) {
            window()->console()
                ->log_notice("No next level set. Changing to end game scene.");

            if (score_ > Highscore::score()) {
                Highscore::score(score_);
                Highscore::write();
            }

            window_->change_scene(new EndGameScene(window_));
        }
        else {
            char lvlbuf[MAX_LEVEL_PATH];
            strcpy_s(lvlbuf, level()->next_level());
            unload_level();
            load_level(lvlbuf);
        }
        return;
	default:
		break;
	}

    /* playablelayer */
    for (auto object : *level_->playable_layer()) {
        object->update(this, delta, keys);
    }

    /* Check collision on movableslayer */ 
    for (auto object : *level_->movables()) {
		AABB queryBox = AABB(object->position(), Vector2(32, 32));

		int count = quadTree_->query_range(queryBox, collisionBuffer_, 0);

		object->check_for_collisions(this, collisionBuffer_, count, delta);

		quadTree_->delete_object(object);
        object->apply_velocity(delta);
		quadTree_->insert_object(object);
    }
	
}

void GameScene::update_viewport()
{
	/* Minimum distance between window edge and the player*/
	const int borderOffset = 215;
    const int borderOffsetTop = 340;
    const int borderOffsetBottom = 100;

	int minx = viewport_.x + borderOffset;
	int maxx = viewport_.x - borderOffset + viewport_.width;

    int miny = viewport_.y + borderOffsetTop;
    int maxy = viewport_.y - borderOffsetBottom + viewport_.height;

	auto pos = player_->position();
	int posx = (int)floor(pos.x);
	int posy = (int)floor(pos.y);

	if (posx < minx) viewport_.x += posx - minx;
	else if (posx > maxx) viewport_.x += posx - maxx;

	if (posy < miny) viewport_.y += posy - miny;
	else if (posy > maxy) viewport_.y += posy - maxy;
}

bool GameScene::check_states()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		if (!pausePressed_)
		{
			if (state() == PLAYING)
				state(PAUSED);
			else
                state(PLAYING);

			pausePressed_ = true;
		}
	}
	else
	{
		pausePressed_ = false;
	}

    if (player()->state() == Actor::DEAD)
	{
        state(PLAYER_DEAD);
		return true;
	}

	return false;
}

void GameScene::render(HDC graphics) {
    if (!level_) return;

    /* Draw background */
    const int image_width = level_->background_width();
    const int image2_width = level_->background_overlay_width();
    Texture tex = { 0, 0, image_width, viewport_.height };
    Texture tex2 = { 0, 0, image2_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        level_->background()->draw(tex, skyx, 0);
	}
    if (level_->background_overlay())
        for (int skyx = -(viewport_.x / 3) % image2_width - image2_width;
            skyx <= viewport_.width; skyx += image2_width) {
        level_->background_overlay()->draw(tex2, skyx, 0);
    }
	/* Render all layers */
    for (auto object : *level_->background_layer()) {
		object->render(viewport_);
	}
    for (auto object : *level_->playable_layer()) {
		object->render(viewport_);
	}
    for (auto object : *level_->foreground_layer()) {
		object->render(viewport_);
	}

    /* Render HUD */
    for (auto hud : hud_) {
        hud->render(graphics);
    }
}

void GameScene::state(State state)
{
	state_ = state;
}

GameScene::State GameScene::state()
{
	return state_;
}