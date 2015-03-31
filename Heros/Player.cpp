/**
 * Player.cpp
 * Defines the Player class.
 */

#include "Player.h"
#include "SpriteSheet.h"
#include "GameScene.h"
#include <stdio.h>

#define WALK_ACCEL          (250.0)
#define DASH_ACCEL          (5000.0)
#define WALK_SPEED          (250.0)
#define WALK_FRICTION	    (550.0)
#define DASH_SPEED			(400.0)

#define ANIMATION_INTERVAL  (0.08)
#define TEXTURE_WIDTH       (22)
#define TEXTURE_HEIGHT      (28)

#define TEX_WIDTH_SNEAK		(24)
#define TEX_HEIGHT_SNEAK    (28)

Player::Player(Vector2 pos) :Actor(pos, Vector2(14, 27)) {
    mainSpriteSheet_ = SpriteSheet::get("spr/MainCharacter.bmp");
    boxSpriteSheet_ = SpriteSheet::get("spr/Box_Sprite.bmp");
}

void Player::update(GameScene *scene, double delta, Keys keys) {
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

    /* Use abilities */
    if (sneakingAbility_)
        sneakingAbility_->use(scene, this, keys);
    if (jumpingAbility_)
        jumpingAbility_->use(scene, this, keys);
    if (sprintingAbility_)
        sprintingAbility_->use(scene, this, keys);
    if (splashingAbility_)
        splashingAbility_->use(scene, this, keys);
    if (duckingAbility_)
        duckingAbility_->use(scene, this, keys);

    /* Check player at end of level? */
    if (scene->level()->is_end_game_right() == 
        position_.x > scene->level()->end_game_x()) {
        scene->state(GameScene::REACHED_END);
        return;
    }

    if (velocity_.x != 0.00)
        isLastMovementLeft_ = velocity_.x < 0;

    /* Process science */
    process_gravity(delta);
	velocity_.truncate_x((keys & KEY_DASH) ? DASH_SPEED : WALK_SPEED);


    /* Update the player animation. */
    AnimationState new_state = get_animation_state(animationFrames_);

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

Player::AnimationState Player::get_animation_state(int &frames) {
    frames = 1;

    if (is_ducking()) { /* Is ducking. */
        if (velocity_.x < 0) { /* Is moving left. */
            return DUCK_LEFT;
        }
        if (velocity_.x > 0) { /* Is moving right. */
            return DUCK_RIGHT;
        }
        return isLastMovementLeft_ ? DUCK_LEFT : DUCK_RIGHT;
    }
    else if (state() == GameScene::PLAYER_DEAD){
        return DEAD_;
    }
    else if (is_splashing()){ /*SPLASH ATTACK*/
        frames = 2;
        return SPLASHING_;
    }
    else if (velocity_.is_zero()){ /* Not moving at all. */
        return isLastMovementLeft_ ? IDLE_LEFT : IDLE_RIGHT;
    }
    else if (is_on_ground()) {/* Is on ground. */

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

void  Player::give_ability(Ability * ability) {
    assert(ability);

    switch (ability->type()) {
    case ABILITY_DUCK:
        duckingAbility_ = ability;
        break;
    case ABILITY_JUMP:
        jumpingAbility_ = ability;
        break;
    case ABILITY_SNEAK:
        sneakingAbility_ = ability;
        break;
    case ABILITY_SPLASH:
        splashingAbility_ = ability;
        break;
    case ABILITY_SPRINT:
        sprintingAbility_ = ability;
        break;
    }
}

void Player::render(Viewport &vp) {
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
		if (!is_sneaking()){
			texture.left = 2 * TEXTURE_WIDTH;
			texture.top = 1 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 0 * TEX_WIDTH_SNEAK + 1;
		}
        break;
    case RUN_LEFT:
		if (!is_sneaking()){
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
        if (!is_sneaking()){
        texture.left = 1 * TEXTURE_WIDTH;
        texture.top = 2 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    case SLIDE_LEFT:
        if (!is_sneaking()){
			texture.left = 1 * TEXTURE_WIDTH;
			texture.top = 3 * TEXTURE_HEIGHT;
		}
		else{
			texture.top = 0 * TEX_HEIGHT_SNEAK;
			texture.left = 3 * TEX_WIDTH_SNEAK;
		}
        break;
    case IDLE_LEFT:
        if (!is_sneaking()){
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
        if (!is_sneaking()){
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

    (is_sneaking() && !is_splashing()
        ? boxSpriteSheet_ 
        : mainSpriteSheet_)->draw(texture, position_, vp);
}

int Player::die() {
    return --lives_;
}

void Player::add_velocity(Vector2 vec){
	velocity_ += vec;
}