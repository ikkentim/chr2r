#pragma once

enum ActorType {
    DOG,
    FLYING_ENEMIE,
    JUMPING_ENEMIE,
    CHARACTER_MARIO,
    CHARACTER_SANIC,
    CHARACTER_MAGIKARP,

};

struct ActorData {
    int x;
    int y;
    ActorType type;
};