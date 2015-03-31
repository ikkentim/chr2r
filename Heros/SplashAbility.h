/**
 * SplashAbility.h
 * Declares the SplashAbility class.
 */
#pragma once

#include "Ability.h"

// The sneaking ability.
class SplashAbility : public Ability {
public:
    // Default constructor
    SplashAbility();

    // Uses the ability for the specified player
    void use(GameScene * scene, Player * player, Keys keys) override;

    // Gets a value indicating whether this ability is currently activated
    bool is_active() override;
private:
    bool isActive_ = false;
};