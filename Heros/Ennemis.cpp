#include "Ennemis.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define GRAVITY     (981.0)

Ennemis::Ennemis(Vector2 pos, Vector2 size) :Actor(pos, size){
	velocity_ = Vector2(WALK_SPEED, 0);
}
Ennemis :: ~Ennemis(){}

void Ennemis::GoLeft(double delta){

	Vector2 hAccel = { -WALK_ACCEL, 0 };
	velocity_ = hAccel;
}

void Ennemis::GoRight(double delta){

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

void Ennemis::Update(double delta, Keys keys){
	Vector2 hGrav = { 0, GRAVITY };
	if (position_.x > 200){
		GoLeft(delta);
	}
	if (position_.x < 20){
		GoRight(delta);
	}

	Falling(hGrav , delta);
}

void Ennemis::EnteredCollision(GameObject * collider)
{
}