#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (5.0f)
#define WALK_SPEED  (5.0f)
#define GRAVITY     (9.81f)
#define FRICTION	(5.0f)

Player::Player(Vector2 pos) :Actor(pos) {
}

void Player::Update(float delta, Keys keys) {
    Vector2 hAccel = { WALK_ACCEL, 0 };
    Vector2 hDecel = { FRICTION, 0 };
	Vector2 hGrav = { 0, GRAVITY };

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
	if (keys & KEY_JUMP && position_.y > 240) { //and ground under player
		velocity_.y = -10;
	}
	else if ( position_.y < 240) {
		velocity_ += (hGrav * delta);

	}
	else if (position_.y > 240) {
		velocity_.y = 0;
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