#include "DialogHUD.h"

DialogHUD::DialogHUD(Player* p, GameScene* scene) : player(p), scene_(scene), wait(0) {
	activedialog = false;
	//test data, probably gonna be moved to character or level
	l1dialog.push_back(DialogLine(true, "Hi There"));
	l1dialog.push_back(DialogLine(false, "Hey"));
	l1dialog.push_back(DialogLine(true, "Nice Weather, huh?"));
	l1dialog.push_back(DialogLine(false, "Certainly, Sir, Myah"));
	
	dialogit = l1dialog.begin();
}

void DialogHUD::EngageDialog(Character* c) {
	character = c;

	activedialog = true;
	dialogit = l1dialog.begin();

}
void DialogHUD::NextLine() {
	dialogit++;
	if (dialogit == l1dialog.end())
	{
		activedialog = false;
		done = true;
	}
}
void DialogHUD::Update(GameScene *scene, double, Keys k) {
	if (k & KEY_JUMP && wait == 0 && activedialog == true) {
		NextLine();
		wait = 30;
	}

	if (!done)
	{
		if (activedialog)
			scene->SetState(GameScene::TALKING);
		else
		{
			scene->SetState(GameScene::PLAYING);
		}
	}
	else
		scene->SetState(GameScene::PLAYING);
	
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

DialogLine::DialogLine(bool plspoken, std::string str) {
	playerspoken = plspoken;
	sentence = str;
}