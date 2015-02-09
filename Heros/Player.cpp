#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (5.0f)
#define WALK_SPEED  (5.0f)
#define GRAVITY     (9.81f)
#define FRICTION	(5.0f)
#define JUMPPOW		(-2.0f)

Player::Player(Vector2 pos, Vector2 size) :Actor(pos, size) {
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
	if (keys & KEY_JUMP && onGround) { 
		velocity_.y = JUMPPOW;

		onGround = false;
    }

	Falling(hGrav, delta);

    velocity_.TruncateX(WALK_SPEED);
}

void Player::Render(Viewport &vp) {
    Texture texture = {
        257, 247,
        16, 16
    };

    SpriteSheet::terrain->Draw(texture, position_, vp);
}

void Player::EnteredCollision(GameObject *object, Vector2 &overlapped)
{
	if (overlapped.y < 0)
		onGround = true;

	Actor::EnteredCollision(object, overlapped);
}