#pragma once

#include "HUD.h"
#include <string>
#include <vector>
class DialogLine;

class DialogHUD : public HUD {
public:
	DialogHUD(Player*);
	void EngageDialog(Character*);
	void NextLine();
	void Update(GameScene*, double, Keys);
	void Render(HDC);
private:
	std::vector<DialogLine> l1dialog;
	std::vector<DialogLine>::iterator dialogit;
	bool activedialog;
	Player* player;
	Character* character;
	int wait;
};

class DialogLine {
public:
	DialogLine(bool, std::string);
	bool playerspoken;
	std::string sentence;
};