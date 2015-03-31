/**
 * SprintAbility.h
 * Declares the SprintAbility class.
 */
#pragma once

#include "Ability.h"

// The sprinting ability.
class SprintAbility : public Ability {
public:
    // Default constructor
    SprintAbility();

    // Uses the ability for the specified player
    void use(GameScene * scene, Player * player, Keys keys) override;

    // Gets a value indicating whether this ability is currently activated
    bool is_active() override;
private:
    bool isActive_ = false;
};