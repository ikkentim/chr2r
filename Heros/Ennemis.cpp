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

void Ennemis::go_left(double delta){

	Vector2 hAccel = { -(WALK_ACCEL + abs(velocity_.x)),0};
	velocity_ += hAccel*delta;
}

void Ennemis::go_right(double delta){

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

void Ennemis::update(GameScene *scene, double delta, Keys keys){
	if (is_dead_state(state())){
		return;
	}

	process_gravity(delta);
}

void Ennemis::entered_collision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (is_dead_state(state())){
		return;
	}
	
	if (obj == scene->player()){
		
		if (scene->player()->velocity().y > 0 && scene->player()->position().y < position_.y){
		//	OutputDebugString("dead");
			state(Actor::DEAD);
			isSolid_ = false;
			scene->player()->add_velocity(Vector2(0, -(scene->player()->velocity().y )*2));
		}
        else if (!scene->player()->is_sneaking()){
			scene->player()->state(Actor::DEAD);
		}
	}
	if (obj != scene->player()){
		if (abs(velocity_.y) < abs(velocity_.x))
		{
		
			 if (velocity_.x < 0){
				go_right(0.6);
			}
			if (velocity_.x > 0){
				go_left(0.60);
			} 
		}
	}
}

bool Ennemis::is_dead_state(State state){
	if (state == DEAD){
		return true;
	}
	return false;
}
