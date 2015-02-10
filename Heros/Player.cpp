#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (250.0)
#define WALK_SPEED  (250.0)
#define GRAVITY     (981.0)
#define FRICTION	(500.0)
#define JUMPPOW		(-300.0)


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
		if (state != DONT_MOVE){
			state = DONT_MOVE;
			animationIndex = 0;
		}
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (velocity_.x > 0 && IsOnGround() == true){
		//Draw animation when you go right
		if (state != GO_RIGHT){
			state = GO_RIGHT;
			animationIndex = 0;
		}
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (velocity_.x < 0 && IsOnGround() == true){
		//Draw animation when you go left
		if (state != GO_LEFT){
			state = GO_LEFT;
			animationIndex = 0;
		}
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (IsOnGround() == false && velocity_.y > 0 && velocity_.x >0){
		//Draw animation when you jump right
		if (state != JUMP_RIGHT){
			state = JUMP_RIGHT;
			animationIndex = 0;
		}

        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (IsOnGround() == false && velocity_.y < 0 && velocity_.x >0){
		//Draw animation when you fall right
		if (state != FALL_RIGHT){
			state = FALL_RIGHT;
			animationIndex = 0;
		}
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (IsOnGround() == false && velocity_.y > 0 && velocity_.x <0){
		//Draw animation when you jump left
		if (state != JUMP_LEFT){
			state = JUMP_LEFT;
			animationIndex = 0;
		}
        if (animationTime > 1){
            ++animationIndex;
            animationTime = 0;
        }
	}
    else if (IsOnGround() == false && velocity_.y < 0 && velocity_.x <0){
		//Draw animation when you fall left
		if (state != FALL_LEFT){
			state = FALL_LEFT;
			animationIndex = 0;
		}
		if (animationTime > 1){
			++animationIndex;
			animationTime = 0;
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
	//TODO: Create Jump right and Jump left Texture
	Texture texture_Jump = {
		animationIndex * 24, 120,
		24, 40
	};
	Texture texture_DontMove = {
		animationIndex * 24, 0,
		24, 40
	};
	


	if (state == GO_RIGHT)
		SpriteSheet::character->Draw(texture_Right, position_, vp);

	if (state == GO_LEFT)
		SpriteSheet::character->Draw(texture_Left, position_, vp);
	if (state == JUMP_LEFT){
		SpriteSheet::character->Draw(texture_Jump, position_, vp);
	}
	if (state == DONT_MOVE){
		SpriteSheet::character->Draw(texture_DontMove, position_, vp);
	}


    /* Temporary texture! Remove when animated character works completely!
     * (or when you are working on the animated character) */
   // SpriteSheet::character->Draw(Texture(0 * 24, 40, 24, 40), position_, vp);
}