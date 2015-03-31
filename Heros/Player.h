/**
 * Player.h
 * Declares the Player class.
 */
#pragma once

#include "Actor.h"
#include "Keys.h"
#include "Ability.h"

// Represents a player
class Player : public Actor {
public:
    enum AnimationState {
		RUN_RIGHT,
		RUN_LEFT,
		JUMP_RIGHT,
		JUMP_LEFT,
		FALL_RIGHT,
		FALL_LEFT,
        DUCK_RIGHT,
        DUCK_LEFT,
        SLIDE_RIGHT,
        SLIDE_LEFT,
		IDLE_RIGHT,
        IDLE_LEFT,
		SPLASHING_,
		SNAKE_,
		DEAD_,

	};

    // A constructor which sets the position of the player
    Player(Vector2);

    // Performs the update logic
    void update(GameScene *, double, Keys) override;

    // Renders the graphics
	void render(Viewport &) override;

    // Die
	int die();

    // Adds the specified value to the velocity
	void add_velocity(Vector2 value);

    // Gives the specified ability to the player
    void give_ability(Ability *ability);
  
    // Gets a value indicating whether the player is sneaking
    bool is_sneaking() {
        return sneakingAbility_ && sneakingAbility_->is_active();
    }

    // Gets a value indicating whether the player is sprinting
    bool is_sprinting() {
        return sprintingAbility_ && sprintingAbility_->is_active();
    }

    // Gets a value indicating whether the player is splashing
    bool is_splashing() {
        return splashingAbility_ && splashingAbility_->is_active();
    }

    // Gets a value indicating whether the player is ducking
    bool is_ducking() {
        return duckingAbility_ && duckingAbility_->is_active();
    }

    // Gets the number of lives left
    int lives() {
        return lives_;
    }

    // Sets the number of lives left
    void lives(int lives) {
        lives_ = lives;
    }

private:
    Ability *sneakingAbility_ = NULL;
    Ability *jumpingAbility_ = NULL;
    Ability *sprintingAbility_ = NULL;
    Ability *splashingAbility_ = NULL;
    Ability *duckingAbility_ = NULL;

    SpriteSheet *mainSpriteSheet_;
    SpriteSheet *boxSpriteSheet_;
    Keys keys_ = KEY_NONE;
    bool isLastMovementLeft_ = false;
	double animationTime_ = 0;
	int animationIndex_ = 0;
    int animationFrames_ = 1;
    AnimationState state_;
    AnimationState get_animation_state(int &frames);
	int lives_ = 3;
};