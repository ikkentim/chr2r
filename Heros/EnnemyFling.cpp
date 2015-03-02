#include "EnnemyFlying.h"
#include <math.h>

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define M_PI		(3.14159265358979323846)



#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (28) //TODO::To define when we add a sprite
#define TEXTURE_HEIGHT      (28) //TODO::To define when we add a sprite

//Here we define the x and y where the enemy start (x=1500, y=18)
EnnemyFlying::EnnemyFlying(Vector2 pos) :Ennemis(Vector2(1500, 18)){
	velocity_ = Vector2(WALK_SPEED, 0);
}

EnnemyFlying :: ~EnnemyFlying(){}

void EnnemyFlying::Render(Viewport &vp) {
	Texture texture_left = { //TODO::We have to define the texture when a sprite will be chosen
		75, 280,
		33, 18
	};
	Texture texture_right = {	//TODO::We have to define the texture when a sprite will be chosen
		236, 280,
		33, 18
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
	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;


	SpriteSheet::Get(SpriteSheet::ENNEMY_1)->Draw(tex, position_, vp);

}

void EnnemyFlying::Update(GameScene *scene, double delta, Keys keys){
	animationTime_ += delta;
	//pattern of the enemy
	int a = 1500;
	int b = 900;
	if (position_.x > a){
		nbTick_++;
		GoLeft(delta,nbTick_);
	}
	if (position_.x < b){
		nbTick_++; 
		GoRight(delta,nbTick_);
	}

	/* Update the player animation. */
	AnimationState new_state = GetAnimationState(animationFrames_);

	if (state_ != new_state) {
		state_ = new_state;
		animationIndex_ = 0;
	}
	else if (animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;

		animationIndex_ = (animationIndex_ + 1) % 2;
	}

	Falling(delta);
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
	Vector2 hAccel = { -WALK_ACCEL, 250 * sin(nbTick*0.5*M_PI) };
	velocity_ = hAccel;
}

void EnnemyFlying::GoRight(double delta,int nbTick){

	Vector2 hAccel = { WALK_ACCEL, 250*sin(nbTick*0.5*M_PI ) };
	velocity_ = hAccel;
}