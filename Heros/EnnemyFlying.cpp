#include "EnnemyFlying.h"
#include <math.h>

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define M_PI		(3.14159265358979323846)



#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (18) 
#define TEXTURE_HEIGHT      (18) 


EnnemyFlying::EnnemyFlying(Vector2 pos) :Ennemis(pos){
	velocity_ = Vector2(/*WALK_SPEED*/0, 50);
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


	SpriteSheet::Get(SpriteSheet::ENNEMY_2)->Draw(tex, position_, vp);

}

void EnnemyFlying::Update(GameScene *scene, double delta, Keys keys){
	animationTime_ += delta;

	nbTick_++;

	if (position_.y>= 240){
		GoLeft(delta, nbTick_);
	}

	if (position_.y <= 100){
		GoRight(delta, nbTick_);
	}
	/* Update the player animation. */
	AnimationState new_state = GetAnimationState(animationFrames_);

/*	if (state_ != new_state) {
		state_ = new_state;
		animationIndex_ = 0;
	}
	else if (animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;

		animationIndex_ = (animationIndex_ + 1) % 2;
	}
*/
	/*There no falling fonction because the enemie fly*/
}

EnnemyFlying::AnimationState EnnemyFlying::GetAnimationState(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving right. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving left. */
		frames = 3;
		return RUN_LEFT;
	}
}

//TODO:: Testing
void EnnemyFlying::GoLeft(double delta,int nbTick){
	Vector2 hAccel = { /*WALK_ACCEL*/0, (250 * sin(nbTick * 0.5 * M_PI)) - 50 };
	velocity_ = hAccel;
}

void EnnemyFlying::GoRight(double delta,int nbTick){

	Vector2 hAccel = { /*WALK_ACCEL*/0, (250*sin(nbTick * 0.5 * M_PI )) }; //(250 * sin(numberOfTicks * 0.5 * pi)) + 350
	velocity_ = hAccel;
}