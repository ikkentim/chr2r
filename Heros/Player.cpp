#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (250.0)
#define WALK_SPEED  (250.0)
#define GRAVITY     (981.0)
#define FRICTION	(150.0)
#define JUMPPOW		(-250.0)

Player::Player(Vector2 pos, Vector2 size) :Actor(pos, size) {
}

static double tmp = 0;
void Player::Update(double delta, Keys keys) {
    tmp = delta;
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
	if (keys & KEY_JUMP) { 
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
	Actor::EnteredCollision(object, overlapped);
}