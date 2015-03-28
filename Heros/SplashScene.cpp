#include "SplashScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

SplashScene::SplashScene(GameWindow *window) :time_(0.0f), window_(window) {
    spriteSheet_ = SpriteSheet::get("spr/splash.bmp");
}

SplashScene::~SplashScene() {
}

void SplashScene::start() {
	window_->sound_engine()->play2D("snd/smb_coin.wav");
}
void SplashScene::update(double delta, Keys) {
    time_ += delta;

    if (time_ > 0.5f) { /* show splash for 0.5 seconds */
        window_->update_scene(new MenuScene(window_));
    }
}

void SplashScene::render(HDC graphics) {
    spriteSheet_->draw(Texture(0, 0, 640, 480), 0, 0);
}