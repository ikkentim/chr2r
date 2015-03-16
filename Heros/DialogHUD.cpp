#include "DialogHUD.h"

DialogHUD::DialogHUD(Player* p, GameScene* scene) : player(p), scene_(scene), wait(0) {
	activedialog = false;
	
}

void DialogHUD::EngageDialog(Character* c) {
	character = c;
	l1dialog = character->dialog;
	activedialog = true;
	dialogit = l1dialog.begin();

}
void DialogHUD::NextLine() {
	dialogit++;
	if (dialogit == l1dialog.end()) //dialog is done
	{
		activedialog = false;
		scene_->SetState(GameScene::PLAYING);
	}
}
void DialogHUD::Update(GameScene *scene, double, Keys k) {
	if (k & KEY_JUMP && wait == 0 && activedialog == true) {
		NextLine();
		wait = 30;
	}

	if (activedialog)
		scene->SetState(GameScene::TALKING);

}

void DialogHUD::Render(HDC hdc) {
	if (activedialog) {

		if (wait > 0)
			wait--;

		std::string text = dialogit->sentence;
		if (dialogit->playerspoken) {
			TextOut(hdc, 150,
				100, text.c_str(), text.length());
		}
		else {
			TextOut(hdc, 400,
				100, text.c_str(), text.length());
		}
	}
}

