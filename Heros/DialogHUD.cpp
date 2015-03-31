/**
 * DialogHUD.cpp
 * Defines the DialogHUD class.
 */

#include "DialogHUD.h"

DialogHUD::DialogHUD(Player* p, GameScene* scene) : player(p), scene_(scene), wait(0) {
	activedialog = false;
	
}

void DialogHUD::engage_dialog(Character* c) {
	character = c;
	l1dialog = character->dialog;
	activedialog = true;
	dialogit = l1dialog.begin();

}
void DialogHUD::next_line() {
	dialogit++;
	if (dialogit == l1dialog.end()) //dialog is done
	{
		activedialog = false;
		scene_->state(GameScene::PLAYING);
	}
}
void DialogHUD::update(GameScene *scene, double delta, Keys k) {
	if (k & KEY_JUMP && wait == 0 && activedialog == true) {
		next_line();
		wait = 30;
	}

	if (activedialog)
		scene->state(GameScene::TALKING);

}

void DialogHUD::render(HDC hdc) {
	if (activedialog) {

		if (wait > 0)
			wait--;

		std::string text = dialogit->sentence;
		if (dialogit->playerspoken) {
			TextOut(hdc, 50,
				100, text.c_str(), text.length());
		}
		else {
			TextOut(hdc, 300,
				100, text.c_str(), text.length());
		}
	}
}

