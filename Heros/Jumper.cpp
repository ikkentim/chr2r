#include "Jumper.h"
#include "SpriteSheet.h"
#include "GameScene.h"

#define JUMP_POWER (600)
#define ANIMATION_INTERVAL  (0.25)

Jumper::Jumper(Vector2 pos) :GameObject(false, pos, Vector2(16, 16)){
	spriteSheet_ = SpriteSheet::Get("spr/Bumper.bmp");
}

void Jumper::Update(GameScene *scene, double delta, Keys keys) {
	animationTime_ += delta;

	if (cooldown == 0)
		animationIndex_ = 0;

	if (cooldown > 0 && animationTime_ >= ANIMATION_INTERVAL) {

		animationTime_ = 0;
		animationIndex_ = (animationIndex_ + 1) % 3;
	}
		
}

void Jumper::EnteredCollision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (cooldown == 0 && obj == scene->player()){
	scene->SoundEngine()->play2D("snd/Jumper.mp3");
		cooldown = 40;
		Vector2 playervel = scene->player()->Velocity();
		Vector2 Jump {0,-JUMP_POWER};
		scene->player()->AddVelocity(Vector2(0, -abs(playervel.y)));
		scene->player()->AddVelocity(Jump);

	}
}

void Jumper::Render(Viewport &vp){
	Texture t0 = { 3, 11, 19, 20 }; //small
	Texture t1 = { 25, 13, 18, 20 }; //medium
	Texture t2 = { 45, 12, 18, 20 }; //big

	if (cooldown > 0)
		cooldown--;

	switch(animationIndex_) {
		case 0:
			spriteSheet_->Draw(t1, position_, vp);
			break;
		case 1:
			spriteSheet_->Draw(t2, position_, vp);
			break;
		case 2:
			spriteSheet_->Draw(t0, position_, vp);
			break;
		}

}