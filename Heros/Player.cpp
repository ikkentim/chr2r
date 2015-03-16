#include "Player.h"
#include "SpriteSheet.h"
#include "GameScene.h"
#include <stdio.h>

#define WALK_ACCEL          (250.0)
#define DASH_ACCEL          (5000.0)
#define WALK_SPEED          (250.0)
#define WALK_FRICTION	    (550.0)
#define JUMP_SPEED		    (-400.0)
#define DASH_SPEED			(400.0)

#define ANIMATION_INTERVAL  (0.08)
#define TEXTURE_WIDTH       (22)
#define TEXTURE_HEIGHT      (28)

#define TEX_WIDTH_SNEAK		(24)
#define TEX_HEIGHT_SNEAK    (28)

Player::Player(GameScene *scene, Vector2 pos) :Actor(pos, Vector2(14, 27)) {
    spriteSheet_ = SpriteSheet::Get("spr/MainCharacter.bmp");
    soundEngine_ = scene->SoundEngine();
}

void Player::Update(GameScene *scene, double delta, Keys keys) {
	animationTime_ += delta;

    /* Update movement according to keys pressed. */
    keys_ = keys;
    if (!(keys & KEY_DOWN) && keys & KEY_RIGHT) {
		velocity_ += (Vector2((keys & KEY_DASH) ? DASH_ACCEL : WALK_ACCEL, 0) * delta);
	} else if (velocity_.x > 0) {
        velocity_ += velocity_ < (Vector2(WALK_FRICTION, 0) * delta)
            ? -velocity_ 
            : (Vector2(-WALK_FRICTION, 0) * delta);
    }

    if (!(keys & KEY_DOWN) && keys & KEY_LEFT) {
		velocity_ -= (Vector2((keys & KEY_DASH) ? DASH_ACCEL : WALK_ACCEL, 0) * delta);
	} else if (velocity_.x < 0) {
        velocity_ -= velocity_ < (Vector2(WALK_FRICTION, 0) * delta)
            ? velocity_ 
            : (Vector2(-WALK_FRICTION, 0) * delta);
    }
    if (keys & KEY_JUMP && IsOnGround() && !isSneaking_) {
        velocity_.y = JUMP_SPEED;

        soundEngine_->play2D("snd/smb_jump-small.wav");
    }

    isDucking_ = !!(keys & KEY_DOWN);

	isSplashing_ = !!(keys & KEY_SPLASH);

	isSneaking_ = !!(keys & KEY_SNEAK);

	if (isSneaking_&& !isSplashing_){
		spriteSheet_ = SpriteSheet::Get("spr/Box_Sprite.bmp");
	}
	else{
		spriteSheet_ = SpriteSheet::Get("spr/MainCharacter.bmp");
	}

    /* Check player at end of level? */
    if (scene->level()->isEndGameRight() == 
        position_.x > scene->level()->endGameX()) {
        scene->SetState(GameScene::REACHED_END);
        return;
    }

    if (velocity_.x != 0.00)
        isLastMovementLeft_ = velocity_.x < 0;

    /* Process science */
    Falling(delta);
	velocity_.TruncateX((keys & KEY_DASH) ? DASH_SPEED:WALK_SPEED);


    /* Update the player animation. */
    AnimationState new_state = GetAnimationState(animationFrames_);

    if (state_ != new_state) {
        state_ = new_state;
        animationIndex_ = 0;
    }
    else if (animationTime_ >= ANIMATION_INTERVAL) {
        animationTime_ -= ANIMATION_INTERVAL;

        /* Limit the animation index to the number of available frames.
         * The number of available frames is calcuated according to the 
         * following table: 
         * 
         * animationFrames_ | number of available frames
         * -----------------+---------------------------
         * 1                | 1
         * 2                | 2
         * 3                | 4
         * 4                | 6
         * 5                | 8
         * ...
         *
         * We need this number of available frames to go back and forth trough
         * all the frames, (0, 1, 2, 1, 0, 1, 2, ...) instead of looping trough
         * the frames (0, 1, 2, 0, 1, 2, ...).
         */
        int available_frames = animationFrames_ > 2 
            ? animationFrames_ * 2 - 2 
            : animationFrames_;

        animationIndex_ = (animationIndex_ + 1) % available_frames;
    }
}

Player::AnimationState Player::GetAnimationState(int &frames) {
    frames = 1;
	
		if (isDucking_) { /* Is ducking. */
			if (velocity_.x < 0) { /* Is moving left. */
				return DUCK_LEFT;
			}
			if (velocity_.x > 0) { /* Is moving right. */
				return DUCK_RIGHT;
			}
			return isLastMovementLeft_ ? DUCK_LEFT : DUCK_RIGHT;
		}
		else if (GetState() == GameScene ::PLAYER_DEAD){
			OutputDebugString("dead");
			return DEAD_;
		}
		else if (isSplashing_){ /*SPLASH ATTACK*/
			frames = 2;
			return SPLASHING_;
		}
		else if (velocity_.IsZero()){ /* Not moving at all. */
			return isLastMovementLeft_ ? IDLE_LEFT : IDLE_RIGHT;
		}
		else if (IsOnGround()) {/* Is on ground. */

			if (velocity_.x > 0) { /* Is moving right. */
				if (keys_ & KEY_LEFT) {
					return SLIDE_RIGHT;
				}
				frames = 3;
				return RUN_RIGHT;
			}
			if (velocity_.x < 0) { /* Is moving left. */
				if (keys_ & KEY_RIGHT) {
					return SLIDE_LEFT;
				}
				frames = 3;
				return RUN_LEFT;
			}
			return isLastMovementLeft_ ? IDLE_LEFT : IDLE_RIGHT;
		}
		else {
			if (velocity_.y < -0.1f) { /* Jumping. */
				if (velocity_.x > 0) { /* Is moving right or straight up. */
					return JUMP_RIGHT;
				}
				if (velocity_.x < 0) { /* Is moving left. */
					return JUMP_LEFT;
				}
				return isLastMovementLeft_ ? JUMP_LEFT : JUMP_RIGHT;
			}
			else { /* Falling */
				if (velocity_.x > 0) { /* Is moving right or straight up. */
					return FALL_RIGHT;
				}
				if (velocity_.x < 0) { /* Is moving left. */
					return FALL_LEFT;
				}
				return isLastMovementLeft_ ? FALL_LEFT : FALL_RIGHT;
			}
		}
}

void Player::Render(Viewport &vp) {
    Texture texture = { 0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT };

    switch (state_) {
	case SNAKE_:
		texture.top = 3 * TEX_HEIGHT_SNEAK;
		texture.left = 1 * TEX_WIDTH_SNEAK;

	case SPLASHING_:
		texture.top = 3 * TEXTURE_HEIGHT;
		texture.left = 2 * TEXTURE_WIDTH + 6;
		break;
	case DEAD_:
		texture.top = 2 * TEXTURE_HEIGHT;
		texture.left = 2 * TEXTURE_WIDTH;
		break;
	
    case DUCK_RIGHT:
        texture.left = 0 * TEXTURE_WIDTH;
        texture.top = 1 * TEXTURE_HEIGHT;
        break;
    case DUCK_LEFT:
        texture.left = 0 * TEXTURE_WIDTH;
        texture.top = 0 * TEXTURE_HEIGHT;
        break;
    case RUN_RIGHT:
		if (!isSneaking_){
			texture.left = 2 * TEXTURE_WIDTH;
			texture.top = 1 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 0 * TEX_WIDTH_SNEAK + 1;
		}
        break;
    case RUN_LEFT:
		if (!isSneaking_){
			texture.left = 2 * TEXTURE_WIDTH;
			texture.top = 0 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 1 * TEX_HEIGHT_SNEAK;
			texture.left = 0 * TEX_WIDTH_SNEAK + 2;
		}
        break;
    case JUMP_RIGHT:
    case FALL_RIGHT:
        texture.left = 1 * TEXTURE_WIDTH;
        texture.top = 1 * TEXTURE_HEIGHT;
        break;
    case JUMP_LEFT:
    case FALL_LEFT:
        texture.left = 1 * TEXTURE_WIDTH;
        texture.top = 0 * TEXTURE_HEIGHT;
        break;
    case SLIDE_RIGHT:
		if (!isSneaking_){
        texture.left = 1 * TEXTURE_WIDTH;
        texture.top = 2 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    case SLIDE_LEFT:
		if (!isSneaking_){
			texture.left = 1 * TEXTURE_WIDTH;
			texture.top = 3 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    case IDLE_LEFT:
		if (!isSneaking_){
			texture.left = 4 * TEXTURE_WIDTH;
			texture.top = 0 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    case IDLE_RIGHT:
    default:
		if (!isSneaking_){
			 texture.left = 4 * TEXTURE_WIDTH;
			 texture.top = 1 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    }

    /* Calculate the frame that should be shown based on the animationIndex_.
     */
    int idx = animationIndex_ > 2 
        ? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2) 
        : animationIndex_;

    texture.left += idx * TEXTURE_WIDTH;

    spriteSheet_->Draw(texture, position_, vp);
}

bool Player::Die()
{
	if (IsDeadState(GetState())){
		OutputDebugString("dead !! 2");
		
		}
	
	if (--lives_ <= 0)
		return true;

	position_.x = 0;
	position_.y = 0;

	return false;
}

bool Player::IsDeadState(State state){
	if (state == DEAD){
		
		return true;
	}
	return false;
}

void Player::AddVelocity(Vector2 vec){
	velocity_ += vec;
}