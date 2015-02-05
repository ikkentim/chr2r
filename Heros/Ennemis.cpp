#include "Ennemis.h"

#define WALK_SPEED  (3.0f)
#define WALK_ACCEL  (3.0f)
#define GRAVITY     (9.81f)
#define MASS		(60.0f)

Ennemis::Ennemis(Vector2 pos) :Actor(pos){}
Ennemis :: ~Ennemis(){}

void Ennemis::GoLeft(float delta){

	Vector2 hAccel = { -WALK_ACCEL, 0 };

	if (position_.x < 50){
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

	if (position_.x > 150){
		collision = true;
	}

	if (!collision){
		velocity_ += hAccel;
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
	//TODO Define the floor we can't jump if we don't touch the floor or if we don't are on a block
	Vector2 hGravity = { 0, MASS*GRAVITY };
	bool onBlock = true;
	if (onBlock){
		//TODO take the jumping method of Jurgen :D
	}
}

void Ennemis::Render() {
	Texture texture = {
		257, 247,
		16, 16
	};

	SpriteSheet::terrain->Draw(texture, position_);
}

void Ennemis::Update(float delta, Keys k){

	GoLeft(delta);
}