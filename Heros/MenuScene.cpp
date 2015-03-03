#include "MenuScene.h"
#include "GameScene.h"

#define KEY_INTERVAL            (0.15)

MenuScene::MenuScene(GameWindow *window) :window_(window) {
	
}

MenuScene::~MenuScene() {
	if (window_)
		window_->SoundEngine()->stopAllSounds();
}
void MenuScene::Start() {
	auto sound = window_->SoundEngine()->play2D("snd/jaz30.s3m", true, false, true);
	sound->setVolume(0.5f);
	sound->drop();
}
void MenuScene::Update(double delta, Keys k) {

    if (keyDelay_ > 0)
        keyDelay_ -= delta;
    
    if (k & KEY_DOWN && keyDelay_ <= 0) {
        keyDelay_ = KEY_INTERVAL;
        selectedOption_ = (selectedOption_ + 1) % 3;
	}

    if ((k & KEY_UP && keyDelay_ <= 0)) {
        keyDelay_ = KEY_INTERVAL;
        selectedOption_ = (selectedOption_ + 2) % 3;
	}

	if ((k & KEY_JUMP)) {	

        switch (selectedOption_) {
			case 0:
				window_->UpdateScene(new GameScene(window_));
				break;
			case 1:
				break;
			case 2:
				exit(0);
			}
	}
}

void MenuScene::Render(double delta, HDC graphics) {

	int xoff = 100;
	int yoff = 190;
	int yspc = 50;
	SpriteSheet::Get(SpriteSheet::MENU_SCREEN)->Draw(Texture(0, 0, 640, 480), 0, 0);
	SpriteSheet::Get(SpriteSheet::PLAY_BUTTON)->Draw(Texture(0, 0, 126, 41), xoff, yoff);
	SpriteSheet::Get(SpriteSheet::OPTIONS_BUTTON)->Draw(Texture(0, 0, 126, 41), xoff, yoff + yspc);
	SpriteSheet::Get(SpriteSheet::EXIT_BUTTON)->Draw(Texture(0, 0, 126, 41), xoff, yoff + yspc * 2);
	SpriteSheet::Get(SpriteSheet::ARROW)->Draw(Texture(0, 0, 63, 40), xoff-80, yoff + yspc * selectedOption_);//alter ypos for cursor
}