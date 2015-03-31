/**
 * Ability.h
 * Declares the abstract Ability class.
 */
#pragma once

#include "Keys.h"
#include "Abilities.h"

class Player;
class GameScene;

// Contains method declartions for a player ability
class Ability {
public:
    // Gets the type of this ability
    Abilities type() {
        return type_;
    }

    // Uses the ability for the specified player
    virtual void use(GameScene * scene, Player * player, Keys keys) = 0;

    // Gets a value indicating whether this ability is currently activated
    virtual bool is_active() = 0;
protected:
    // Default constructor
    Ability(Abilities type) :
        type_(type) { }

    Abilities type_;
};