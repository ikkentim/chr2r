#include "EndGameScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

EndGameScene::EndGameScene(GameWindow *window) :position_(0.0f), window_(window) {
    spriteSheet_ = SpriteSheet::Get("spr/credits.bmp");
}

EndGameScene::~EndGameScene() {
}

void EndGameScene::Start() {
    window_->SoundEngine()->play2D("snd/07-castle-complete.mp3");
}

void EndGameScene::Update(double delta, Keys) {
    position_ += delta * 100;

    if (position_ > 900.0f) {
        window_->UpdateScene(new MenuScene(window_));
    }
}

void EndGameScene::Render(HDC graphics) {

    const int maxy = 1200 - 480;
    int y = min((int)position_, maxy);
    spriteSheet_->Draw(Texture(0, y, 640, 480), 0, 0);
}