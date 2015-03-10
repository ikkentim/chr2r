#pragma once

enum ActorType {
    DOG,
    FLYING_ENEMIE,
    JUMPING_ENEMIE,
    CHARACTER
};

struct ActorData {
    int x;
    int y;
    ActorType type;
};