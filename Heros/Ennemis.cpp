#include "Ennemis.h"

#define WALK_SPEED  (3.0f)
#define WALK_ACCEL  (3.0f)
#define GRAVITY     (9.81f)

Ennemis::Ennemis(Vector2 pos) :Actor(pos){}
Ennemis :: ~Ennemis(){}

void Ennemis::GoLeft(float delta){

	Vector2 hAccel = { -WALK_ACCEL, 0 };

	if (position_.x < 30){
		collision = true;
	}

	if (!collision){
		velocity_ += hAccel * delta;
	}
	velocity_.Truncate(WALK_SPEED);

	if (collision){
		collision = false;
		velocity_.x = 0;
		GoRight(delta);
	}
	position_ += velocity_;
}

void Ennemis::GoRight(float delta){

	Vector2 hAccel = { WALK_ACCEL, 0 };

	if (position_.x > 200){
		collision = true;
	}

	if (!collision){
		velocity_ += hAccel * delta;
	}

	velocity_.Truncate(WALK_SPEED);

	if (collision){
		collision = false;
		velocity_.x = 0;
		GoLeft(delta);
	}
	position_ += velocity_;
}

void Ennemis::Jump(float delta){
/*	bool onGround = (position_.y > 240);
	int mass = 2;
	Vector2 hGrav = { 0, GRAVITY*mass };

	if (jump){
		if ( onGround) {
			velocity_.y = -10;
		}
		else if (!onGround) {
			velocity_ += (hGrav * delta);

		}
		else if (onGround) {
			velocity_.y = 0;
		}
		jump = false;
	}
*/
}

void Ennemis::Render(Viewport &vp) {
	Texture texture = {
		257, 247,
		16, 16
	};

	SpriteSheet::terrain->Draw(texture, position_, vp);
}

void Ennemis::Update(float delta, Keys k){
	velocity_ = Vector2(-3, 0);
	//GoLeft(delta);
/*	int i = rand() % 100;
*	if (i > 80){
*		jump = true;
*		Jump(delta);
*	}
*/
	position_ += velocity_;
}