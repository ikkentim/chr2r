#pragma once

enum ActorType {
    DOG,
    FLYING_ENEMIE,
    JUMPING_ENEMIE,
    CHARACTER_MARIO,
    CHARACTER_SANIC,
    CHARACTER_MAGIKARP,
	CHARACTER_SNAKE

};

struct ActorData {
    int x;
    int y;
    ActorType type;
};