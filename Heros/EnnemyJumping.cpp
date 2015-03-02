#include "EnnemyJumping.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define JUMP_ACCEL	(100.0)


#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (28) //TODO::To define when we add a sprite
#define TEXTURE_HEIGHT      (28) //TODO::To define when we add a sprite

//Here we define the x and y where the enemy start (x=1500, y=18)
EnnemyJumping::EnnemyJumping(Vector2 pos) :Ennemis(Vector2(1500, 18)){
	velocity_ = Vector2(WALK_SPEED, 0);
}

EnnemyJumping :: ~EnnemyJumping(){}

void EnnemyJumping::Render(Viewport &vp) {
	Texture texture_left = { //TODO::We have to define the texture when a sprite will be chosen
		75, 280,
		33, 18
	};
	Texture texture_right = {	//TODO::We have to define the texture when a sprite will be chosen
		236, 280,
		33, 18
	};
	Texture texture_jump = {//TODO::We have to define the texture when a sprite will be chosen
		123,123,
		123,123
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
	case JUMP_:

		tex = texture_jump;
		break;
	}
	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;


	SpriteSheet::Get(SpriteSheet::ENNEMY_1)->Draw(tex, position_, vp);

}

void EnnemyJumping::Update(GameScene *scene, double delta, Keys keys){
	animationTime_ += delta;
	//pattern of the enemy
	int a = 1500;
	int b = 900;
	if (position_.x > a){
		GoLeft(delta);
	}
	if (position_.x < b){
		GoRight(delta);
	}
	if (position_.y <= 0){
		Jump(delta);
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

EnnemyJumping::AnimationState EnnemyJumping::GetAnimationState(int &frames) {
	frames = 1;

	if (velocity_.x > 0) { /* Is moving right. */
		frames = 3;
		return RUN_RIGHT;
	}
	if (velocity_.x < 0) { /* Is moving left. */
		frames = 3;
		return RUN_LEFT;
	}
	if (velocity_.y > 0){ /*Is Jumping.*/
		frames = 3;
		return JUMP_;
	}
}

void EnnemyJumping::Jump(double delta){
	Vector2 hAccel = { 0, JUMP_ACCEL };
	velocity_ += hAccel; /*I put a += otherwise the Ennemie will stop running*/
}
