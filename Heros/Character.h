/**
 * Character.h
 * Declares the abstract Character class.
 */
#pragma once

#include "Actor.h"
#include "Ability.h"

class DialogLine;

// Represents a tutor character
class Character : public Actor {
public:
    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
	virtual void render(Viewport &vp) = 0;

    // The dialogue to display when in contact with the player
	std::vector<DialogLine> dialog;
protected:
    // A constructor which sets the position and size of the character
	Character(Vector2 position, Vector2 size);

	Ability * ability;
	SpriteSheet *spriteSheet_;
	bool finisheddialog = false;
};

class DialogLine {
public:
	DialogLine(bool, std::string);
	bool playerspoken;
	std::string sentence;
};
