/**
 * DialogHUD.h
 * Declares the DialogHUD class.
 */
#pragma once
#include "GameScene.h"
#include "Player.h"
#include "Character.h"
#include "IHUD.h"
#include <string>
#include <vector>

// Represents a dialogue hud element
class DialogHUD : public IHUD {
public:
    // Constructor which sets the player and scene
	DialogHUD(Player *player, GameScene *scene);

    // Displays the dialogue for the specified character
	void engage_dialog(Character *);

    // Proceedes to the next dialogue line
	void next_line();

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
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
