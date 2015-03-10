#include "Jumper.h"
#include "SpriteSheet.h"
#include "GameScene.h"

#define JUMP_POWER (1000)
#define ANIMATION_INTERVAL  (0.5)

Jumper::Jumper(Vector2 pos) :GameObject(false, pos, Vector2(12, 8)){
	spriteSheet_ = SpriteSheet::Get("spr/Bumper.bmp");
}

void Jumper::Update(GameScene *scene, double delta, Keys keys) {
	animationTime_ += delta;
	if (JumpON && animationIndex_ == 2){
		JumpON = false;
		animationIndex_ = 0;
	}

	if (JumpON && animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;
		animationIndex_ = (animationIndex_ + 1) % 3;
	}
}

void Jumper::EnteredCollision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (!JumpON && obj == scene->player()){
	scene->SoundEngine()->play2D("snd/Jumper.mp3");

		JumpON = true;
		Vector2 Jump {0,-JUMP_POWER};
		scene->player()->AddVelocity(Jump);

	}
}

void Jumper::Render(Viewport &vp){
	Texture t0 = { 3, 11, 19, 20 }; //small
	Texture t1 = { 25, 13, 18, 20 }; //medium
	Texture t2 = { 45, 12, 18, 20 }; //big


	if (!JumpON){
		spriteSheet_->Draw(t1, position_, vp);
	}

	if (JumpON){
		switch (animationIndex_) {
		case 0:
			spriteSheet_->Draw(t0, position_, vp);
			break;
		case 1:
			spriteSheet_->Draw(t1, position_, vp);
			break;
		case 2:
			spriteSheet_->Draw(t2, position_, vp);
			break;
		}
	}

}