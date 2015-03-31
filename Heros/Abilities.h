/**
 * Abilities.h
 * Contains definitions for every available ability type and declares the 
 * Abilities type.
 */
#pragma once

#define ABILITY_NONE        (0)
#define ABILITY_JUMP        (1)
#define ABILITY_SPRINT      (2)
#define ABILITY_SPLASH      (4)
#define ABILITY_SNEAK       (8)
#define ABILITY_DUCK        (16)

// Holds a bit field of available abilities.
typedef int Abilities;