#pragma once

#include "Actor.h"
#include "Keys.h"
#include <irrKlang.h>
#include "Ability.h"

class Player : public Actor {
public:
    enum AnimationState{
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

    Player(class GameScene *, Vector2);
    void update(GameScene *, double, Keys) override;
	void render(Viewport &) override;
	bool die();
	void add_velocity(Vector2);
    void give_ability(Ability *);
	Vector2 velocity(){
		return velocity_;
    }
    bool is_sneaking() {
        return sneakingAbility_ && sneakingAbility_->is_active();
    }
    bool is_sprinting() {
        return sprintingAbility_ && sprintingAbility_->is_active();
    }
    bool is_splashing() {
        return splashingAbility_ && splashingAbility_->is_active();
    }
    bool is_ducking() {
        return duckingAbility_ && duckingAbility_->is_active();
	}
	int lives_ = 3;
private:
	bool Player::is_dead_state(State);

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
    irrklang::ISoundEngine *soundEngine_;

    AnimationState get_animation_state(int &frames);
};