/**
 * DuckAbility.h
 * Declares the DuckAbility class.
 */
#pragma once

#include "Ability.h"

// The ducking ability.
class DuckAbility : public Ability {
public:
    // Default constructor
    DuckAbility();

    // Uses the ability for the specified player
    void use(GameScene * scene, Player * player, Keys keys) override;

    // Gets a value indicating whether this ability is currently activated
    bool is_active() override;
private:
    bool isActive_ = false;
};