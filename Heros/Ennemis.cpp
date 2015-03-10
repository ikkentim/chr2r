#include "Ennemis.h"
#include "GameScene.h"
#include "Actor.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)


Ennemis::Ennemis(Vector2 pos, SpriteSheet *spriteSheet) :Actor(pos, Vector2(16, 16)){
	//velocity_ = Vector2(WALK_SPEED, 0);
    spriteSheet_ = spriteSheet;

}
Ennemis :: ~Ennemis(){}

void Ennemis::GoLeft(double delta){

	Vector2 hAccel = { -(WALK_ACCEL + abs(velocity_.x)),0};
	velocity_ += hAccel*delta;
}

void Ennemis::GoRight(double delta){

	Vector2 hAccel = { WALK_ACCEL + abs(velocity_.x), 0 };
	velocity_ += hAccel*delta;
}


/*void Ennemis::Render(Viewport &vp) {
	Texture texture = {
		257, 247,
		16, 16
	};

	SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(texture, position_, vp);
}*/

void Ennemis::Update(GameScene *scene, double delta, Keys keys){
	if (IsDeadState(GetState())){
		return;
	}

	Falling(delta);
}

void Ennemis::EnteredCollision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (IsDeadState(GetState())){
		return;
	}
	
	if (obj == scene->player()){
		if (scene->player()->GetVelocity().y > 0)
			OutputDebugString("vel");
		if (scene->player()->Position().y < position_.y)
			OutputDebugString("pos");
		if (scene->player()->GetVelocity().y > 0 && scene->player()->Position().y < position_.y){
			OutputDebugString("dead");
			SetState(Actor::DEAD);
			isSolid_ = false;
			scene->player()->AddVelocity(Vector2(0, -(scene->player()->GetVelocity().y )*2));
		}
		else{ 
			scene->player()->SetState(Actor::DEAD);
		}
	}
	if (obj != scene->player()){
		if (abs(velocity_.y) < abs(velocity_.x))
		{
		
			 if (velocity_.x < 0){
				GoRight(0.6);
			}
			if (velocity_.x > 0){
				GoLeft(0.60);
			} 
		}
	}
}

bool Ennemis::IsDeadState(State state){
	if (state == DEAD){
		return true;
	}
	return false;
}
