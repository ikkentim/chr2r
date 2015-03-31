/**
 * Keys.h
 * Contains definitions for every available key and declares the Keys type.
 */
#pragma once

#define KEY_NONE        (0)

#define KEY_LEFT        (1)
#define KEY_RIGHT       (2)
#define KEY_JUMP        (4)
#define KEY_UP          (8)
#define KEY_DOWN        (16)

#define KEY_L           (32)
#define KEY_O           (64)
#define KEY_DELETE      (128)

#define KEY_DASH		(256)
#define KEY_SPLASH		(512)
#define KEY_SNEAK		(1024)

// Holds a bit field of keys.
typedef int Keys;