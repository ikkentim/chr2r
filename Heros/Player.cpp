#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (250.0)
#define WALK_SPEED  (250.0)
#define GRAVITY     (981.0)
#define FRICTION	(500.0)
#define JUMPPOW		(-400.0)


Player::Player(Vector2 pos, Vector2 size) :Actor(pos, size) {
}

void Player::Update(double delta, Keys keys) {
    Vector2 hAccel = { WALK_ACCEL, 0 };
    Vector2 hDecel = { FRICTION, 0 };
	Vector2 hGrav = { 0, GRAVITY };
	animationTime += delta;


    if (keys & KEY_RIGHT) {
        velocity_ += (hAccel * delta);
	} else if (velocity_.x > 0) {
        velocity_ += velocity_ < (hDecel * delta) ? -velocity_ : (-hDecel * delta);
    }

	if (keys & KEY_LEFT) {
		velocity_ -= (hAccel * delta);
	} else if (velocity_.x < 0) {
		velocity_ -= velocity_ < (hDecel * delta) ? velocity_ : (-hDecel * delta);
    }
    if (keys & KEY_JUMP && IsOnGround()) {
		velocity_.y = JUMPPOW;
    }

	Falling(hGrav, delta);

    velocity_.TruncateX(WALK_SPEED);

	if (velocity_ == Vector2(0, 0)){
		//Draw animation when you don't move
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = DONT_MOVE;
        }
	}
    else if (velocity_.x > 0 && IsOnGround() == true){
		//Draw animation when you go right
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = GO_RIGHT;
        }
	}
    else if (velocity_.x < 0 && IsOnGround() == true){
		//Draw animation when you go left
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = GO_LEFT;
        }
	}
    else if (IsOnGround() == false && velocity_.y > 0 && velocity_.x >0){
		//Draw animation when you jump right
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = JUMP_RIGHT;
        }
	}
    else if (IsOnGround() == false && velocity_.y < 0 && velocity_.x >0){
		//Draw animation when you fall right
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = FALL_RIGHT;
        }
	}
    else if (IsOnGround() == false && velocity_.y > 0 && velocity_.x <0){
		//Draw animation when you jump left
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
            state = JUMP_LEFT;
        }
	}
    else if (IsOnGround() == false && velocity_.y < 0 && velocity_.x <0){
		//Draw animation when you fall left
		if (animationTime > 1){
			++animationIndex;
			animationTime = 0;
			state = FALL_LEFT;
		}
	}
	if (animationIndex >= 4){
		animationIndex = 0;
	}
}

void Player::Render(Viewport &vp) {
	//TODO: Add new all texture and if test for the character when we will select a good sprite =)
    Texture texture_Right = {
        animationIndex*24, 80,
        24, 40
    };
	Texture texture_Left = {
		animationIndex * 24, 40,
		24, 40
    };

	if (state == GO_RIGHT)
    SpriteSheet::character->Draw(texture_Right, position_, vp);

	if (state == GO_LEFT)
		SpriteSheet::character->Draw(texture_Left, position_, vp);


    /* Temporary texture! Remove when animated character works completely!
     * (or when you are working on the animated character) */
    SpriteSheet::character->Draw(Texture(0 * 24, 40, 24, 40), position_, vp);
}