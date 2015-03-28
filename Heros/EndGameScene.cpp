#include "EndGameScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

EndGameScene::EndGameScene(GameWindow *window) :position_(0.0f), window_(window) {
    spriteSheet_ = SpriteSheet::get("spr/credits.bmp");
}

EndGameScene::~EndGameScene() {
}

void EndGameScene::start() {
    window_->sound_engine()->play2D("snd/07-castle-complete.mp3");
}

void EndGameScene::update(double delta, Keys) {
    position_ += delta * 100;

    if (position_ > 900.0f) {
        window_->update_scene(new MenuScene(window_));
    }
}

void EndGameScene::render(HDC graphics) {

    const int maxy = 1200 - 480;
    int y = min((int)position_, maxy);
    spriteSheet_->draw(Texture(0, y, 640, 480), 0, 0);
}