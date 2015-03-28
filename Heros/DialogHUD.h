#pragma once
#include "GameScene.h"
#include "Player.h"
#include "Character.h"
#include "HUD.h"
#include <string>
#include <vector>

class DialogHUD : public HUD {
public:
	DialogHUD(Player*, GameScene*);

	void engage_dialog(Character*);
	void next_line();
    void update(GameScene*, double, Keys) override;
	void render(HDC) override;
private:
	std::vector<DialogLine> l1dialog;
	std::vector<DialogLine>::iterator dialogit;
	bool activedialog;
	Player* player;
	GameScene *scene_;
	Character* character;
	int wait;
};
