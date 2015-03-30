#pragma once

#include "Ability.h"

class SprintAbility : public Ability {
public:
    SprintAbility();
    void use(GameScene * scene, Player * player, Keys keys) override;
    bool is_active() override;
private:
    bool isActive_ = false;
};