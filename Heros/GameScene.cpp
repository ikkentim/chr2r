#include "GameScene.h"
#include "Block.h"

GameScene::GameScene(GameWindow *window) {
    viewport_ = { 0, 0, 640, 480 };

    /* push basic level */
    level_ = new LevelManager();

    Vector2 player_spawn = { 64, 48 };
    player_ = new Player(player_spawn);


    Vector2 Ennemis_spawn = { 80, 50 };
    ennemis_ = new Ennemis{ Ennemis_spawn };

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

    /* Update all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;

        object->Update(delta, keys);
    }

    /* Render all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;

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

        object->Render(viewport_);
    }

}