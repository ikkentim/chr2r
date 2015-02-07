#include "Ennemis.h"

#define WALK_SPEED  (1.0f)
#define WALK_ACCEL  (1.0f)
#define GRAVITY     (9.81f)

Ennemis::Ennemis(Vector2 pos, Vector2 size) :Actor(pos, size){
	velocity_ = Vector2(WALK_SPEED, 0);
}
Ennemis :: ~Ennemis(){}

void Ennemis::GoLeft(float delta){

	Vector2 hAccel = { -WALK_ACCEL, 0 };
	velocity_ = hAccel;
}

void Ennemis::GoRight(float delta){

	Vector2 hAccel = { WALK_ACCEL, 0 };
	velocity_ = hAccel;
}



void Ennemis::Render(Viewport &vp) {
	Texture texture = {
		257, 247,
		16, 16
	};

	SpriteSheet::terrain->Draw(texture, position_, vp);
}

void Ennemis::Update(float delta, Keys k){
	Vector2 hGrav = { 0, GRAVITY };
	onGround = (position_.y > 240);

	if (position_.x > 200){
		GoLeft(delta);
	}
	if (position_.x < 20){
		GoRight(delta);
	}

	Falling(hGrav , delta);
}