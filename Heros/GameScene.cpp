#include "GameScene.h"
#include "Block.h"

GameScene::GameScene(GameWindow *window)
    :viewport_(Viewport(0, 0, 640, 480)) {

    /* Load a level manager for testing purposes. */
    level_ = new LevelManager();

    /* Load a player and an enemy for testing purposes. */
    Vector2 player_spawn = { 64, 48 };
	Vector2 size = { 16, 16 };
	player_ = new Player(player_spawn, size);
    level_->PlayableLayer()->push_back(player_);

    Vector2 ennemis_spawn = { 80, 50 };
    ennemis_ = new Ennemis( ennemis_spawn, size );
    level_->PlayableLayer()->push_back(ennemis_);

    /* Load a number of object for testing purposes. */
	Texture grass_top = { 444, 253, 16, 16 };
	for (int x = 0; x < 15; x++) {
		level_->PlayableLayer()->push_back(
            new Block(grass_top, { 16.0f * x, 256.0f }));
	}

	for (int x = 0; x < 5; x++) {
		level_->PlayableLayer()->push_back(
            new Block(grass_top, { 16.0f * x, 220.0f }));
	}

	for (int x = 8; x < 15; x++) {
		level_->PlayableLayer()->push_back(
            new Block(grass_top, { 16.0f * x, 190.0f }));
	}

    for (int y = 0; y < 25; y++) {
        level_->PlayableLayer()->push_back(
            new Block(grass_top, { 256.0f, 256.0f - 16.0f * y }));
    }

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
    for (LevelLayer::iterator iter = layer->begin(); 
        iter != layer->end(); ++iter) {
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
    LevelLayer *layer = level_->PlayableLayer();

    /* Draw background */
    /* FIXME: Make LevelManager decide background */
    /* FIXME: backgrounds can have different widths */
    const int image_width = 727;
    Texture tex = { 0, 0, image_width, viewport_.height };
    for (int skyx = (viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        SpriteSheet::background01->Draw(tex, skyx, 0);
    }

    /* Render all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Render(viewport_);
    }
}