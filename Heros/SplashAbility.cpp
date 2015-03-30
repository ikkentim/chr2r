#include "SplashAbility.h"
#include "Player.h"
#include "GameScene.h"

SplashAbility::SplashAbility() :
Ability(ABILITY_SPLASH) {

}

void SplashAbility::use(GameScene * scene, Player * player, Keys keys) {
    isActive_ = !!(keys & KEY_SPLASH);
}

bool SplashAbility::is_active() {
    return isActive_;
}