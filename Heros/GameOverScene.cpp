#include "GameOverScene.h"
#include "MenuScene.h"
#include "SpriteSheet.h"

GameOverScene::GameOverScene(GameWindow *window) :position_(0.0f), window_(window) {
	spriteSheet_ = SpriteSheet::Get("spr/gameover.bmp");
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::Start() {
	window_->SoundEngine()->play2D("snd/09-game-over.mp3");
}

void GameOverScene::Update(double delta, Keys) {
	time_ += delta;

	if (time_ > 1)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			window_->UpdateScene(new MenuScene(window_));
			return;
		}
	}
}

void GameOverScene::Render(HDC graphics) {

	const int maxy = 1200 - 480;
	int y = min((int)position_, maxy);
	spriteSheet_->Draw(Texture(0, y, 640, 480), 0, 0);
}