#include "SplashScene.h"
#include "GameScene.h"

SplashScene::SplashScene(GameWindow *window) :time_(0.0f), window_(window) {
    auto tune = window->SoundEngine()
        ->play2D("snd/smb_coin.wav", false, false, true);
    //tune->setVolume(0.3f);
    //tune->drop();
}

SplashScene::~SplashScene() {
}

void SplashScene::Update(float delta, Keys) {
    time_ += delta;

    Texture tex = {
        0, 0, 640, 480
    };
    Vector2 vec = { 0, 0 };
    Viewport vp = {
        0, 0, 0, 0
    };

    SpriteSheet::splash->Draw(tex, vec, vp);

    if (time_ > 0.5f) { /* show splash for 0.5 seconds */
        window_->UpdateScene(new GameScene(window_));
    }

}