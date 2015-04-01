/**
 * MenuScene.cpp
 * Defines the MenuScene class.
 */

#include "MenuScene.h"
#include "GameScene.h"
#include "Highscore.h"

#define KEY_INTERVAL            (0.15)

MenuScene::MenuScene(GameWindow *window) :window_(window) {
    spriteSheet_ = SpriteSheet::get("spr/menu.bmp");
    spriteSheetPlay_ = SpriteSheet::get("spr/play_button.bmp");
    spriteSheetExit_ = SpriteSheet::get("spr/exit_button.bmp");
    spriteSheetArrow_ = SpriteSheet::get("spr/arrow_button.bmp");
}

MenuScene::~MenuScene() {
	if (window_)
		window_->sound_engine()->stopAllSounds();
}
void MenuScene::start() {
	auto sound = window_->sound_engine()->play2D("snd/jaz30.s3m", true, false, true);
	sound->setVolume(0.5f);
	sound->drop();

    Highscore::read();

    window_->console()->register_command("clearhighscore", 
        [](Console * const console, const char * args)-> bool {
        Highscore::score(0);
        Highscore::write();
        return true;
    });
}
void MenuScene::update(double delta, Keys k) {

    if (keyDelay_ > 0)
        keyDelay_ -= delta;
    
    if ((k & KEY_DOWN || k & KEY_UP) && keyDelay_ <= 0) {
        keyDelay_ = KEY_INTERVAL;
        selectedOption_ = (selectedOption_ + 1) % 2;
	}

	if ((k & KEY_JUMP)) {	

        switch (selectedOption_) {
			case 0:
				window_->change_scene(new GameScene(window_));
				break;
			case 1:
				exit(0);
			}
	}
}

void MenuScene::render(HDC graphics) {

	const int xoff = 100;
	const int yoff = 190;
	const int yspc = 50;
	spriteSheet_->draw(Texture(0, 0, 640, 480), 0, 0);
    spriteSheetPlay_->draw(Texture(0, 0, 126, 41), xoff, yoff);
    spriteSheetExit_->draw(Texture(0, 0, 126, 41), xoff, yoff + yspc);
    spriteSheetArrow_->draw(Texture(0, 0, 63, 40), xoff - 80, yoff + 
        yspc * selectedOption_);//alter ypos for cursor

    char buf[64];

    sprintf_s(buf, "Highscore: %d", Highscore::score());
    TextOut(graphics, 5, 455, buf, strlen(buf));
}