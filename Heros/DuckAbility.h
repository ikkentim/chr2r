#pragma once

#include "Ability.h"

class DuckAbility : public Ability {
public:
    DuckAbility();
    void use(GameScene * scene, Player * player, Keys keys) override;
    bool is_active() override;
private:
    bool isActive_ = false;
};