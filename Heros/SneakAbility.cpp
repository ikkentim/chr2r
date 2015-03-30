#include "SneakAbility.h"
#include "Player.h"
#include "GameScene.h"

SneakAbility::SneakAbility() :
Ability(ABILITY_SNEAK) {

}

void SneakAbility::use(GameScene * scene, Player * player, Keys keys) {
    isActive_ = !!(keys & KEY_SNEAK);
}

bool SneakAbility::is_active() {
    return isActive_;
}