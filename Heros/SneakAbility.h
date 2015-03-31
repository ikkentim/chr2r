/**
 * SneakAbility.h
 * Declares the SneakAbility class.
 */
#pragma once

#include "Ability.h"

// The sneaking ability.
class SneakAbility : public Ability {
public:
    // Default constructor
    SneakAbility();

    // Uses the ability for the specified player
    void use(GameScene * scene, Player * player, Keys keys) override;

    // Gets a value indicating whether this ability is currently activated
    bool is_active() override;
private:
    bool isActive_ = false;
};