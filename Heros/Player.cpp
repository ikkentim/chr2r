#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (5.0f)
#define WALK_SPEED  (5.0f)
#define GRAVITY     (9.81f)
#define FRICTION	(5.0f)
#define JUMPPOW		(-10.0f)

Player::Player(Vector2 pos) :Actor(pos) {
}

void Player::Update(float delta, Keys keys) {
    Vector2 hAccel = { WALK_ACCEL, 0 };
    Vector2 hDecel = { FRICTION, 0 };
	Vector2 hGrav = { 0, GRAVITY };

	bool onGround = (position_.y > 240); // if character is on ground, add collision stuff here, (pos y > 240) is a placeholder

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
	if (keys & KEY_JUMP && onGround) { 
		velocity_.y = JUMPPOW;
	} else if (!onGround) {
		velocity_ += (hGrav * delta);
	} else if (onGround) {
		if (velocity_.y > 2)
			position_.y -= velocity_.y;
		
		velocity_.y -= velocity_.y;
	}
    velocity_.Truncate(WALK_SPEED);

    position_ += velocity_;
}

void Player::Render() {
    Texture texture = {
        257, 247,
        16, 16
    };

    SpriteSheet::terrain->Draw(texture, position_);
}