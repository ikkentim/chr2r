#include "EnnemyFlying.h"
#include <math.h>

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define M_PI		(3.14159265358979323846)



#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (18) 
#define TEXTURE_HEIGHT      (18) 



/*EnnemyFlying::EnnemyFlying(Vector2 pos) :Ennemis(pos){
	velocity_ = Vector2(-WALK_SPEED, -WALK_SPEED);
	start_position = pos;
*/
	EnnemyFlying::EnnemyFlying(Vector2 pos) :Ennemis(pos, SpriteSheet::Get("spr/Zelda_Enemies_Sprite.bmp")){
		velocity_ = Vector2(-WALK_SPEED, -WALK_SPEED);
		start_position = pos;

}

EnnemyFlying :: ~EnnemyFlying(){}

void EnnemyFlying::Render(Viewport &vp) {
	Texture texture_left = { 
		56, 241,
		18, 18
	};
	Texture texture_right = {
		56, 241,
		18, 18
	};

	Texture tex = texture_right;

	switch (state_) {
	case RUN_RIGHT:
		//	SpriteSheet::Get(SpriteSheet::ENNEMY_1)->Draw(texture_right, position_, vp);
		tex = texture_right;
		break;
	case RUN_LEFT:

		//	SpriteSheet::Get(SpriteSheet::ENNEMY_1)->Draw(texture_left, position_, vp);
		tex = texture_left;
		break;
	}
	//The Enemie don't have animation

	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;


	spriteSheet()->Draw(tex, position_, vp);

}

void EnnemyFlying::Update(GameScene *scene, double delta, Keys keys){
	animationTime_ += delta;

	nbTick_++;

	if (position_.y < start_position.y - 100){
		GoDown(delta, nbTick_); //GoDown
	}

	if (position_.y > start_position.y || IsOnGround()){
		GoUp(delta, nbTick_); //GoUp
	}
	if (position_.x <= start_position.x - 100){
		GoRight(delta); 
	}

	if (position_.x >= start_position.x + 100){
		GoLeft(delta);
	}
	/* Update the player animation. */
	AnimationState new_state = GetAnimationState(animationFrames_);

	/*There no falling fonction because the enemie fly*/
}

EnnemyFlying::AnimationState EnnemyFlying::GetAnimationState(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving Up. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving Down. */
		frames = 3;
		return RUN_LEFT;
    }

    return RUN_RIGHT;/* todo: make an idle state? */
}


void EnnemyFlying::GoDown(double delta,int nbTick){ //Go Down

	Vector2 hAccel1 = { 0, (400 * abs(sin(nbTick * 0.5 * M_PI))) + abs(velocity_.y )};
	
	velocity_ += hAccel1*delta;
}

void EnnemyFlying::GoUp(double delta,int nbTick){ //Go UP

	Vector2 hAccel1 = {0, -((400*abs(sin(nbTick * 0.5 * M_PI))) + abs(velocity_.y))};

	velocity_ += hAccel1*delta;
}