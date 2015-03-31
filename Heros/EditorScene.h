/**
 * EditorScene.h
 * Declares the EditorScene class.
 */
#pragma once

#include "IScene.h"
#include <string>
#include "GameWindow.h"
#include "Viewport.h"
#include "SpriteSheet.h"
#include "LevelHeader.h"
#include <vector>
#include "ObjectData.h"
#include "ActorData.h"
#include <map>

#define MAX_GAME_OBJECT_TYPE_NAME_LENGTH  (32)

// Represents a level editor scene
class EditorScene : public IScene {
public:
    // A constructor which sets the gamewindow
    EditorScene(GameWindow * window);

    // Default destructor
    ~EditorScene() override;

    // Initialises the scene
    void start() override;

    // Performs the update logic
    void update(double, Keys) override;

    // Renders the graphics
    void render(HDC graphics) override;

    // Loads the level from the specified path
    void load(const char *path);

    // Saves the level to the specified path
    void save(const char *path);

    // Sets the background
    void background(const char *background);

    // Sets the background overlay
    void background_overlay(const char *background);

    // Sets the terrain texture sheet
    void terrain(const char *terrain);

    // Sets the backgound music
    void sound(const char *path);

    // Sets the next level
    void next_level(const char *path);

    // Sets the background width
    void background_width(int backgroundWidth);

    // Sets the background overlay width
    void background_overlay_width(int backgroundWidth);

    // Sets the bottom y coordinate under which the player dies
    void bottom_y(int y);

    // Moves the cursor to the specified X- and Y-coordinates
    void go_to(int x, int y);

    // Set the X-coordinate the player needs to reach to win
    void end_game_x(int x);

    // Sets the player spawn coordinates
    void player_spawn(int x, int y);

    // Gets the current cursor position
    void current_pos(int &x, int &y);

    // Sets the grid size
    void grid_size(int size);

    // Selects the specified texture
    void select_texture(int left, int top, int width, int height);

    // Toggles the visibility of the specified layer
    bool toggle_layer_visible(LevelManager::Layer layer);

    // Toggles the availability of the specified ability
    bool toggle_ability_type(Abilities type);

private:
    struct GameObjectTypeData {
        char name[MAX_GAME_OBJECT_TYPE_NAME_LENGTH];
        int width = 0;
        int height = 0;
        SpriteSheet * spriteSheet = NULL;
        Texture texture = Texture(0, 0, 0, 0);

        GameObjectTypeData() {
            ZeroMemory(name, MAX_GAME_OBJECT_TYPE_NAME_LENGTH);
        }

        GameObjectTypeData(const char * n, int w, int h, SpriteSheet * s, 
            Texture t) {
            strcpy_s(name, n);
            width = w;
            height = h;
            spriteSheet = s;
            texture = t;
        }
    };

    GameWindow *window_;
    Viewport viewport_;
    void update_viewport();

    void add_object(std::vector<ObjectData> *, ObjectData);
    void remove_object(std::vector<ObjectData> *, Vector2);
    void add_actor(ActorData);
    void remove_actor(Vector2);
    std::vector<ObjectData> *current_layer();

    std::map<ObjectType, GameObjectTypeData> objectTypes_;
    std::map<ActorType, GameObjectTypeData> actorTypes_;

    Vector2 cursorPos_ = Vector2(0, 0);
    Vector2 cursorVelocity_ = Vector2(0, 0);

    char sound_[MAX_SOUND_NAME];
    char backgroundPath_[MAX_TEXTURE_PATH];
    char backgroundOverlayPath_[MAX_TEXTURE_PATH];
    char terrainPath_[MAX_TEXTURE_PATH];
    char nextLevel_[MAX_LEVEL_PATH];

    int endGameX_ = 0;
    int backgroundWidth_ = 100;
    int backgroundOverlayWidth_ = 100;
    int bottomY_ = 0;
    int playerX_ = 0;
    int playerY_ = 0;
    int gridSize_ = 1;
    Abilities abilities_ = ABILITY_NONE;

    SpriteSheet *background_ = NULL;
    SpriteSheet *backgroundOverlay_ = NULL;
    SpriteSheet *terrain_ = NULL;
    
    std::vector<ObjectData> playableLayer_;
    std::vector<ObjectData> foregroundLayer_;
    std::vector<ObjectData> backgroundLayer_;
    std::vector<ActorData> actors_;
    
    bool showPlayableLayer_ = true;
    bool showForegroundLayer_ = true;
    bool showBackgroundLayer_ = true;
    bool isKeyDown_ = false;

    LevelManager::Layer currentLayer_ = LevelManager::PLAYABLE;
    Texture selectedTexture_ = { 0, 0, 0, 0 };
    ObjectType currentObjectType_;
    ActorType currentActorType_;
};