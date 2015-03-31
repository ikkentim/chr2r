/**
 * JumpAbility.cpp
 * Defines the JumpAbility class.
 */

#include "JumpAbility.h"
#include "Player.h"
#include "GameScene.h"

#define JUMP_SPEED (400.0)

JumpAbility::JumpAbility() :
    Ability(ABILITY_JUMP) {

}
void JumpAbility::use(GameScene * scene, Player * player, Keys keys) {
    if (keys & KEY_JUMP && player->is_on_ground() && !player->is_sneaking()) {
        scene->sound_engine()->play2D("snd/smb_jump-small.wav");
        player->add_velocity(Vector2(0, -JUMP_SPEED));
    }
}

bool JumpAbility::is_active() {
    return false;
}