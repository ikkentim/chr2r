/**
 * SprintAbility.cpp
 * Defines the SprintAbility class.
 */

#include "SprintAbility.h"

#include "Player.h"
#include "GameScene.h"

SprintAbility::SprintAbility() :
Ability(ABILITY_SPRINT) {

}

void SprintAbility::use(GameScene * scene, Player * player, Keys keys) {
    isActive_ = !!(keys & KEY_DASH);
}

bool SprintAbility::is_active() {
    return isActive_;
}