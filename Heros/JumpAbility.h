/**
 * JumpAbility.h
 * Declares the JumpAbility class.
 */
#pragma once

#include "Ability.h"

// The jumping ability.
class JumpAbility : public Ability {
public:
    // Initializes a new instance of the JumpAbility class.
    JumpAbility();

    // Uses the ability for the specified player
    void use(GameScene * scene, Player * player, Keys keys) override;

    // Gets a value indicating whether this ability is currently activated
    bool is_active() override;
};