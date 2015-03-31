#include "Jumper.h"
#include "SpriteSheet.h"
#include "GameScene.h"

#define JUMP_POWER (600)
#define ANIMATION_INTERVAL  (0.25)

Jumper::Jumper(Vector2 pos) :GameObject(false, pos, Vector2(15, 16)){
	spriteSheet_ = SpriteSheet::get("spr/Bumper.bmp");
}

void Jumper::update(GameScene *scene, double delta, Keys keys) {
	animationTime_ += delta;

	if (cooldown == 0)
		animationIndex_ = 0;

	if (cooldown > 0 && animationTime_ >= ANIMATION_INTERVAL) {

		animationTime_ = 0;
		animationIndex_ = (animationIndex_ + 1) % 3;
	}
		
}

void Jumper::entered_collision(GameScene *scene, GameObject *obj, Vector2 vec) {
	if (cooldown == 0 && obj == scene->player()){
	scene->sound_engine()->play2D("snd/Jumper.mp3");
		cooldown = 40;
		Vector2 playervel = scene->player()->velocity();
		Vector2 Jump {0,-JUMP_POWER};
		scene->player()->add_velocity(Vector2(0, -abs(playervel.y)));
        scene->player()->add_velocity(Jump);

	}
}

void Jumper::render(Viewport &vp){
	//Texture t0 = { 3, 11, 19, 20 }; //small
	//Texture t1 = { 25, 13, 18, 20 }; //medium
	//Texture t2 = { 45, 12, 18, 20 }; //big
    Texture t0 = { 4, 14, 15, 16}; //small
    Texture t1 = { 26, 14, 15, 16 }; //medium
    Texture t2 = { 47, 14, 15, 16 }; //big

	if (cooldown > 0)
		cooldown--;

	switch(animationIndex_) {
		case 0:
			spriteSheet_->draw(t1, position_, vp);
			break;
		case 1:
            spriteSheet_->draw(t2, position_, vp);
			break;
		case 2:
            spriteSheet_->draw(t0, position_, vp);
			break;
		}

}