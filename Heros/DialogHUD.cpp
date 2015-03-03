#include "DialogHUD.h"

DialogHUD::DialogHUD(Player* p) {
	player = p;
	wait = 0;
	//test data
	l1dialog.push_back(DialogLine(true, "Hi There"));
	l1dialog.push_back(DialogLine(false, "Hey"));
	l1dialog.push_back(DialogLine(true, "Nice Weather, huh?"));
	
}

void DialogHUD::EngageDialog(Character* c) {
	character = c;
	activedialog = true;
	dialogit = l1dialog.begin();

}
void DialogHUD::NextLine() {
	dialogit++;
}
void DialogHUD::Update(GameScene*, double, Keys k) {
	if (k & KEY_JUMP && wait == 0) {
		NextLine();
		wait = 30;
	}
}

void DialogHUD::Render(HDC hdc) {
	if (wait > 0)
		wait--;
	std::string text = dialogit->sentence;
	if (dialogit->playerspoken) {
		TextOut(hdc, player->Position().x, 
			player->Position().y - 100, text.c_str(), 6);
	}
	else {
		TextOut(hdc, character->Position().x, 
			character->Position().y - 100, text.c_str(), 6);
	}
}

DialogLine::DialogLine(bool plspoken, std::string str) {
	playerspoken = plspoken;
	sentence = str;
}