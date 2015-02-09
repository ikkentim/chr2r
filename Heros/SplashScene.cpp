#include "SplashScene.h"
#include "GameScene.h"

SplashScene::SplashScene(GameWindow *window) :time_(0.0f), window_(window) {
    auto tune = window->SoundEngine()
        ->play2D("snd/smb_coin.wav", false, false, true);
    tune->setVolume(0.3f);
    tune->drop();
}

SplashScene::~SplashScene() {
}

void SplashScene::Update(double delta, Keys) {
    time_ += delta;

    if (time_ > 0.5f) { /* show splash for 0.5 seconds */
        window_->UpdateScene(new GameScene(window_));
    }
}

void SplashScene::Render(double delta) {
    SpriteSheet::splash->Draw(Texture(0, 0, 640, 480), 0, 0);
}