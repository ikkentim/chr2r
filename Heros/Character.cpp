#include "Character.h"
#include "GameScene.h"
#include "DialogHUD.h"
Character::Character(Vector2 pos, Vector2 box): Actor(pos, box) {
    
}

void Character::update(GameScene* scene, double delta, Keys) {
	if (!finisheddialog && scene->player()->position().distance(position_) < 50) {
		scene->dialog_->engage_dialog(this);
		finisheddialog = true;
		//TODO: teach lesson
        if (ability) {
            scene->player()->give_ability(ability);
        }
        else {
            scene->window()->console()
                ->log_error("Character has no set ability");
        }
	}
	process_gravity(delta);
}

DialogLine::DialogLine(bool plspoken, std::string str) {
	playerspoken = plspoken;
	sentence = str;
}