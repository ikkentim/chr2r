#pragma once

#include "Keys.h"
#include "Abilities.h"
class Player;
class GameScene;

class Ability {
public:
    AbilityType type() {
        return type_;
    }
    virtual void use(GameScene * scene, Player * player, Keys keys) = 0;
    virtual bool is_active() = 0;
protected:
    Ability(AbilityType type) :
        type_(type) { }
    AbilityType type_;
};