/**
 * GameOverScene.cpp
 * Defines the GameOverScene class.
 */

#include "GameOverScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

GameOverScene::GameOverScene(GameWindow *window) : window_(window) {
	spriteSheet_ = SpriteSheet::get("spr/gameover.bmp");
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::start() {
	window_->sound_engine()->play2D("snd/09-game-over.mp3");
}

void GameOverScene::update(double delta, Keys keys) {
	time_ += delta;

    if (time_ > 1 && ((keys & KEY_JUMP) || GetAsyncKeyState(VK_RETURN))) {
        window_->change_scene(new MenuScene(window_));
    }
}

void GameOverScene::render(HDC graphics) {
	spriteSheet_->draw(Texture(0, 0, 640, 480), 0, 0);
}