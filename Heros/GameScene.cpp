#include "GameScene.h"
#include "Block.h"

GameScene::GameScene(GameWindow *window) {
    viewport_ = { 0, 0, 640, 480 };

    /* push basic level */
    level_ = new LevelManager();

    Vector2 player_spawn = { 64, 48 };
	Vector2 size = { 16, 16 };
	player_ = new Player(player_spawn, size);


    Vector2 ennemis_spawn = { 80, 50 };
    ennemis_ = new Ennemis( ennemis_spawn, size );

    Texture grass_top = { 444, 253, 16, 16 };
    for (int x = 0; x < 15; x++) {
        level_->PlayableLayer()->push_back(new Block(grass_top, { 16.0f * x, 256.0f }));
    }

    for (int y = 0; y < 25; y++) {
        level_->PlayableLayer()->push_back(new Block(grass_top, { 256.0f, 256.0f - 16.0f * y }));
    }

    level_->PlayableLayer()->push_back(player_);
    level_->PlayableLayer()->push_back(ennemis_);

}

GameScene::~GameScene() {
    delete level_;
    delete player_;
    delete ennemis_;
}

void GameScene::Update(float delta, Keys keys) {
    LevelLayer *layer = level_->PlayableLayer();

	GameObject *object;
	GameObject *object2;

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

    /* Draw background */
    /* FIXME: Make LevelManager decide background */
    const int image_width = 727;/* FIXME: backgrounds can have different widths */
    Texture tex = { 0, 0, image_width, viewport_.height };
    for (int skyx = (viewport_.x / 2) % image_width - image_width; 
        skyx <= viewport_.width; skyx += image_width) {
        SpriteSheet::background01->Draw(tex, 
            viewport_.Position() + Vector2(skyx, 0), viewport_);
	}

	/* Check collision on playerlayer */
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		object = *it;

		for (LevelLayer::iterator it2 = layer->begin(); it2 != layer->end(); ++it2) {
			if (it == it2)
				continue;

			object2 = *it2;

			Vector2 overlapping;

			if (object->CollidesWith(object2, overlapping))
			{
				object->EnteredCollision(object2, overlapping);
			}

		}
	}

    /* Render all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Render(viewport_);
    }
}