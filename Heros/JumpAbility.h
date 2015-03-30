#pragma once

#include "Ability.h"

class JumpAbility : public Ability {
public:
    JumpAbility();
    void use(GameScene * scene, Player * player, Keys keys) override;
    bool is_active() override;
};