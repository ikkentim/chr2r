#pragma once
#include "Actor.h"
#include "Ability.h"

class DialogLine;
class Character : public Actor {
public:
	Character(Vector2, Vector2);

    void update(GameScene*, double, Keys) override;
	virtual void render(Viewport &vp) = 0;


	std::vector<DialogLine> dialog;
protected:
	Ability ability;
	SpriteSheet *spriteSheet_;
	bool finisheddialog = false;

};

class DialogLine {
public:
	DialogLine(bool, std::string);
	bool playerspoken;
	std::string sentence;
};
