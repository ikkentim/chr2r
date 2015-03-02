#include "SplashScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

SplashScene::SplashScene(GameWindow *window) :time_(0.0f), window_(window) {
    
}

SplashScene::~SplashScene() {
}

void SplashScene::Start() {
	window_->SoundEngine()->play2D("snd/smb_coin.wav");
}
void SplashScene::Update(double delta, Keys) {
    time_ += delta;

    if (time_ > 0.5f) { /* show splash for 0.5 seconds */
        window_->UpdateScene(new MenuScene(window_));
    }
}

void SplashScene::Render(double delta) {
    SpriteSheet::Get(SpriteSheet::SPLASH_SCREEN)->Draw(Texture(0, 0, 640, 480), 0, 0);
}