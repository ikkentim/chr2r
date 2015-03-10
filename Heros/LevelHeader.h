#pragma once

#define MAX_LEVEL_NAME      (32)
#define MAX_TEXTURE_PATH    (32)
#define MAX_LEVEL_PATH      (32)

struct LevelHeader {
    int bottom;
    int player_x;
    int player_y;
    int player_abilities_ph;
    char name[MAX_LEVEL_NAME];
    char background_texture[MAX_TEXTURE_PATH];
    char next_level[MAX_LEVEL_PATH];
    int background_width;
    char terrain_texture[MAX_TEXTURE_PATH];
    int object_count;
    int actor_count;
};