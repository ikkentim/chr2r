#include "EnnemyDog.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)


#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (36)
#define TEXTURE_HEIGHT      (28)


//TOFIX:: pass position when Enemie is create
EnnemyDog::EnnemyDog(Vector2 pos) :Ennemis(Vector2(36, 20), SpriteSheet::Get("spr/metalgearsheet.bmp")){
	velocity_ = Vector2(WALK_SPEED, 0);
}

EnnemyDog :: ~EnnemyDog(){}

void EnnemyDog::Render(Viewport &vp) {
	Texture texture_left = {
		75, 280,
		33, 18
	};
	Texture texture_right = {
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


	spriteSheet()->Draw(tex, position_, vp);
		
}

void EnnemyDog::Update(GameScene *scene, double delta, Keys keys){
	animationTime_ += delta;
	//pattern of the enemy
	int a= 1000; 
	int b=600;
	if (position_.x > a){
		GoLeft(delta);
	}
	if (position_.x < b){
		GoRight(delta);
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

EnnemyDog::AnimationState EnnemyDog::GetAnimationState(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving right. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving left. */
		frames = 3;
		return RUN_LEFT;
	}

    return RUN_RIGHT;/* todo: make an idle state? */
}