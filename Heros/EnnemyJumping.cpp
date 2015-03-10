#include "EnnemyJumping.h"

#define WALK_ACCEL  (150.0)
#define WALK_SPEED  (150.0)
#define JUMP_ACCEL	(400.0)


#define ANIMATION_INTERVAL  (0.4)
#define TEXTURE_WIDTH       (12) 
#define TEXTURE_HEIGHT      (17) 


EnnemyJumping::EnnemyJumping(Vector2 pos) :Ennemis(pos, SpriteSheet::Get("spr/Zelda_Enemies_Sprite.bmp")){

	velocity_ = Vector2(WALK_SPEED, 0);
}

EnnemyJumping :: ~EnnemyJumping(){}

void EnnemyJumping::Render(Viewport &vp) {
	if (IsDeadState(GetState())){
		return;
	}
	Texture texture_OnGround = { 
		164, 288,
		12, 17
	};
	Texture texture_jump = {
		164, 288,
		12, 17
	};
	Texture tex = texture_OnGround;

	switch (state_) {
	case RUN_RIGHT:
		tex = texture_OnGround;
		break;
	case JUMP_:
		tex = texture_jump;
		break;
	}

	int idx = animationIndex_ > 6
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	tex.left += idx * TEXTURE_WIDTH;

	spriteSheet()->Draw(tex, position_, vp);

}

void EnnemyJumping::Update(GameScene *scene, double delta, Keys keys){
	if (IsDeadState(GetState())){
		return;
	}
	animationTime_ += delta;
	//pattern of the enemie

	if (IsOnGround()){
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
	if (!IsOnGround()){ /*Is Jumping.*/
		frames = 3;
		return JUMP_;
    }

    return RUN_RIGHT;/* todo: make an idle state? */
}

void EnnemyJumping::Jump(double delta){
	Vector2 hAccel = { 0, -JUMP_ACCEL };
	velocity_ += hAccel;
}
