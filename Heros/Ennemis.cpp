#include "Ennemis.h"
#include "GameScene.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)


Ennemis::Ennemis(Vector2 pos) :Actor(pos, Vector2(16, 16)){
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

	SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(texture, position_, vp);
}

void Ennemis::Update(GameScene *scene, double delta, Keys keys){
	if (position_.x > 200){
		GoLeft(delta);
	}
	if (position_.x < 20){
		GoRight(delta);
	}

	Falling(delta);
}

void Ennemis::EnteredCollision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (obj == scene->player()){
		scene->player()->SetState(Actor::DEAD);
	}
}