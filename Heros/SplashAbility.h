#pragma once

#include "Ability.h"

class SplashAbility : public Ability {
public:
    SplashAbility();
    void use(GameScene * scene, Player * player, Keys keys) override;
    bool is_active() override;
private:
    bool isActive_ = false;
};