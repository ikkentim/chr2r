#include "EndGameScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

EndGameScene::EndGameScene(GameWindow *window) :time_(0.0f), window_(window) {
    spriteSheet_ = SpriteSheet::Get("spr/splash.bmp");
}

EndGameScene::~EndGameScene() {
}

void EndGameScene::Start() {
}

void EndGameScene::Update(double delta, Keys) {
    time_ += delta;

    if (time_ > 10.0f) {
        window_->UpdateScene(new MenuScene(window_));
    }
}

void EndGameScene::Render(HDC graphics) {
    spriteSheet_->Draw(Texture(0, 0, 640, 480), 0, 0);
}