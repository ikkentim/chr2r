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

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    
    hud_ = new HUDVector;
	level_ = LevelManager::load("lvl/level01.dat", this, player_);

	state_ = PLAYING;
	dialog_ = new DialogHUD(player_, this);
	hud_->push_back(dialog_);


	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

    for (auto object : *level_->playable_layer()) {
		minX = min(minX, object->position().x);
		maxX = max(maxX, object->position().x);
		minY = min(minY, object->position().y);
		maxY = max(maxY, object->position().y);
}

	int boxX = (minX + maxX) / 2;
	int boxY = (minY + maxY) / 2;

	quadTree_ = new QuadTree(new AABB(Vector2(boxX, boxY), Vector2(maxX - minX + 100, maxY - minY + 100)));

	/* playablelayer */
    for (auto object : *level_->playable_layer()) {
		if (object == NULL || object == player())
			continue;

		quadTree_->insert_object(object);
	}
}

GameScene::~GameScene() {
    delete level_;
	delete quadTree_;
	delete dialog_;
}
void GameScene::start() {
    if (strlen(level_->sound()))
        sound_engine()->play2D(level_->sound(), true);
}
void GameScene::update(double delta, Keys keys) {
	update_viewport();
	check_states();

    for (auto hud : *hud_) {
		hud->update(this, delta, keys);
	}
	switch (state_)
	{
	case PAUSED:
		return;
	case TALKING:
		return;
	case PLAYER_DEAD:
		if (player()->die())
		{
			window_->change_scene(new GameOverScene(window_));
			return;
		}
		player()->state(Player::ALIVE);
		state_ = PLAYING;
		return;
    case REACHED_END:
        
        if (level_->is_last_level()) {
            window_->change_scene(new EndGameScene(window_));
        }
        else {
            delete level_;
            level_ = LevelManager::load(level_->next_level(), this, player_);

            sound_engine()->stopAllSounds();
            if (strlen(level_->sound()))
                sound_engine()->play2D(level_->sound(), true);
            state(PLAYING);
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
		AABB* queryBox = new AABB(object->position(), Vector2(32, 32));

		int count = quadTree_->query_range(queryBox, collisionBuffer_, 0);

		delete queryBox;

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

	if (level_->bottom_y() < player()->position().y)
	{
		player()->state(Actor::DEAD);
        state(PLAYER_DEAD);
	}

    if (player()->state() == Actor::DEAD)
	{
        state(PLAYER_DEAD);
		return true;
	}

	return false;
}

void GameScene::render(HDC graphics) {

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
    for (auto hud : *hud_) {
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