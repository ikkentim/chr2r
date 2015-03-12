#include "Character.h"
#include "GameScene.h"
#include "DialogHUD.h"
Character::Character(Vector2 pos, Vector2 box): Actor(pos, box) {
    
}

void Character::Update(GameScene* scene, double delta, Keys) {
	if (!finisheddialog && scene->player()->Position().Distance(position_) < 50) {
		scene->dialog_->EngageDialog(this);
		finisheddialog = true;
		//TODO: teach lesson
	}
	Falling(delta);
}

