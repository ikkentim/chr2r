/**
 * DuckAbility.cpp
 * Defines the DuckAbility class.
 */

#include "DuckAbility.h"
#include "Player.h"
#include "GameScene.h"

DuckAbility::DuckAbility() :
Ability(ABILITY_DUCK) {

}

void DuckAbility::use(GameScene * scene, Player * player, Keys keys) {
    isActive_ = !!(keys & KEY_DOWN);
}

bool DuckAbility::is_active() {
    return isActive_;
}