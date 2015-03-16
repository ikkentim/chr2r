#pragma once
#include "GameScene.h"
#include "Player.h"
#include "Character.h"
#include "HUD.h"
#include <string>
#include <vector>


//class DialogLine;

class DialogHUD : public HUD {
public:
	DialogHUD(Player*, GameScene*);
	void EngageDialog(Character*);
	void NextLine();
	void Update(GameScene*, double, Keys);
	void Render(HDC);
private:
	std::vector<DialogLine> l1dialog;
	std::vector<DialogLine>::iterator dialogit;
	bool activedialog;
	Player* player;
	GameScene *scene_;
	Character* character;
	int wait;
};
