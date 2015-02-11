#include "GameScene.h"
#include "Block.h"

#include <irrKlang.h>

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    /* Start some testing sounds */
    SoundEngine()->play2D("snd/01-main-theme-overworld.mp3", true);

	Texture grass_top = { 444, 253, 16, 16 };
	Texture grass_middle = { 444, 270, 16, 16 };

	Texture grass_tl = { 427, 202, 16, 16 };
	Texture grass_tr = { 461, 202, 16, 16 };

	Texture grass_left = { 427, 219, 16, 16 };
	Texture grass_right = { 461, 219, 16, 16 };

	Texture air_block = { 257, 97, 16, 16 };
	Texture question = { 208, 181, 16, 16 };

	Texture pipe_tl = { 1, 179, 16, 15 };
	Texture pipe_tr = { 19, 179, 16, 15 };
	Texture pipe_bl = { 1, 195, 16, 16 };
	Texture pipe_br = { 19, 195, 16, 16 };

    /* Load a level manager for testing purposes. */
    level_ = new LevelManager();

    /* Load a player and an enemy for testing purposes. */
    player_ = new Player(this, Vector2(16, 240), Vector2(14, 27));
    level_->PlayableLayer()->push_back(player_);

    ennemis_ = new Ennemis(Vector2(80, 240), Vector2(16, 16));
	level_->PlayableLayer()->push_back(ennemis_);

	/* Load a number of object for testing purposes. */
	for (int x = -10; x < 25; x++)
		for (int y = 0; y < 20; y++)
			if (x == -10 && y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_tl, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == 24 && y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_tr, { 16.0f * x, 256.0f + 16 * y }));
			else if (y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_top, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == -10)
				level_->ForegroundLayer()->push_back(new Block(grass_left, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == 24)
				level_->ForegroundLayer()->push_back(new Block(grass_right, { 16.0f * x, 256.0f + 16 * y }));
			else
				level_->ForegroundLayer()->push_back(new Block(grass_middle, { 16.0f * x, 256.0f + 16 * y }));

	/* Load a number of object for testing purposes. */
	for (int x = 28; x < 100; x++)
		for (int y = 0; y < 20; y++)
			if (x == 28 && y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_tl, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == 99 && y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_tr, { 16.0f * x, 256.0f + 16 * y }));
			else if (y == 0)
				level_->PlayableLayer()->push_back(new Block(grass_top, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == 28)
				level_->ForegroundLayer()->push_back(new Block(grass_left, { 16.0f * x, 256.0f + 16 * y }));
			else if (x == 99)
				level_->ForegroundLayer()->push_back(new Block(grass_right, { 16.0f * x, 256.0f + 16 * y }));
			else
				level_->ForegroundLayer()->push_back(new Block(grass_middle, { 16.0f * x, 256.0f + 16 * y }));

	/* Load a number of object for testing purposes. */
	for (int x = 0; x < 3; x++) {
		level_->PlayableLayer()->push_back(new Block(air_block, { 96 + (16.0f * x), 192.0f }));
	}

	/* Load a number of object for testing purposes. */
	for (int x = 0; x < 4; x++) {
		level_->PlayableLayer()->push_back(new Block(air_block, { 480 + (16.0f * x), 192 }));
	}

	/* Load a number of object for testing purposes. */
	for (int x = 0; x < 8; x++) {
		level_->PlayableLayer()->push_back(new Block(air_block, { 544 + (16.0f * x), 128 }));
	}

	level_->PlayableLayer()->push_back(new Block(question, { 112, 192.0f }));

	level_->PlayableLayer()->push_back(new Block(pipe_tl, { 256, 224.0f }));
	level_->PlayableLayer()->push_back(new Block(pipe_tr, { 272, 224.0f }));
	level_->PlayableLayer()->push_back(new Block(pipe_bl, { 256, 240 }));
	level_->PlayableLayer()->push_back(new Block(pipe_br, { 272, 240 }));
}

GameScene::~GameScene() {
    delete level_;
    delete player_;
    delete ennemis_;
}

void GameScene::Update(double delta, Keys keys) {
    LevelLayer *layer = level_->PlayableLayer();

    /* Update all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Update(delta, keys);
    }

    /* Update viewport */
    const int borderOffset = 215;

    int minx = viewport_.x + borderOffset;
    int maxx = viewport_.x - borderOffset + viewport_.width;

    int miny = viewport_.y + borderOffset;
    int maxy = viewport_.y - borderOffset + viewport_.height;

    auto pos = player_->Position();
    int posx = (int)floor(pos.x);
    int posy = (int)floor(pos.y);

    if (posx < minx) viewport_.x += posx - minx;
    else if (posx > maxx) viewport_.x += posx - maxx;

    if (posy < miny) viewport_.y += posy - miny;
    else if (posy > maxy) viewport_.y += posy - maxy;

	/* Check collision on playerlayer */
    for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
        GameObject *object = *iter;
        if (object->IsMovable()) {
            object->CheckForCollisions(layer, delta);
        }
	}

	/* Apply all velocities */
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->ApplyVelocity(delta);
	}
}

void GameScene::Render(double delta) {

    /* Draw background */
    /* FIXME: Make LevelManager decide background */
    /* FIXME: backgrounds can have different widths */
    const int image_width = 727;
    Texture tex = { 0, 0, image_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        SpriteSheet::background01->Draw(tex, skyx, 0);
	}

	LevelLayer *layer;

	layer = level_->BackgroundLayer();
	/* Render all layers */
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}
	layer = level_->PlayableLayer();
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}
	layer = level_->ForegroundLayer();
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}
}