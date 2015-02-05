#include "Player.h"
#include "SpriteSheet.h"
#include <stdio.h>

#define WALK_ACCEL  (5.0f)
#define WALK_SPEED  (5.0f)
#define GRAVITY     (9.81f)

Player::Player(Vector2 pos) :Actor(pos) {
}

void Player::Update(float delta, Keys keys) {
    Vector2 hAccel = { WALK_ACCEL, 0 };
    Vector2 hDecel = { GRAVITY, 0 };

    if (keys & KEY_RIGHT) {
        velocity_ += (hAccel * delta);
    }
    else if (velocity_.x > 0) {
        velocity_ += velocity_ < (hDecel * delta) ? -velocity_ : (-hDecel * delta);
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