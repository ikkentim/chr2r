#pragma once

#include "Ability.h"

class SneakAbility : public Ability {
public:
    SneakAbility();
    void use(GameScene * scene, Player * player, Keys keys) override;
    bool is_active() override;
private:
    bool isActive_ = false;
};