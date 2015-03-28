#pragma once
#include "Scene.h"
#include <string>
#include "GameWindow.h"
#include "Viewport.h"
#include "SpriteSheet.h"
#include "LevelHeader.h"
#include <vector>
#include "ObjectData.h"
#include "ActorData.h"

class EditorScene : public Scene {
public:
    EditorScene(GameWindow *);
    ~EditorScene() override;

    void start() override;
    void update(double, Keys) override;
    void render(HDC graphics) override;
    void load(const char *);
    void save(const char *);

    void background(const char *background) {
        strcpy_s(backgroundPath_, background);
        background_ = SpriteSheet::get(background);
    }

    void background_overlay(const char *background) {
        strcpy_s(backgroundOverlayPath_, background);
        backgroundOverlay_ = SpriteSheet::get(background);
    }

    void terrain(const char *terrain) {
        strcpy_s(terrainPath_, terrain);
        terrain_ = SpriteSheet::get(terrain);
    }

    void level_name(const char *name) {
        strcpy_s(levelName_, name);
    }

    void next_level(const char *path) {
        strcpy_s(nextLevel_, path);
    }

    void background_width(int backgroundWidth) {
        backgroundWidth_ = backgroundWidth;
    }

    void background_overlay_width(int backgroundWidth) {
        backgroundOverlayWidth_ = backgroundWidth;
    }

    void bottom_y(int y) {
        bottomY_ = y;
    }

    void go_to(int x, int y) {
        cursorPos_.x = x;
        cursorPos_.y = y;
    }

    void end_game_x(int x) {
        endGameX_ = x;
    }

    void player_spawn(int x, int y) {
        playerX_ = x;
        playerY_ = y;
    }

    void current_pos(int &x, int &y) {
        x = ((int)cursorPos_.x / gridSize_) * gridSize_;
        y = ((int)cursorPos_.y / gridSize_) * gridSize_;
    }

    void grid_size(int size) {
        gridSize_ = size;
    }

    void select_texture(int left, int top, int width, int height) {
        selectedTexture_.left = left;
        selectedTexture_.top = top;
        selectedTexture_.width = width;
        selectedTexture_.height = height;
    }

    bool toggle_layer_visible(LevelManager::Layer layer) {
        switch (layer) {
        case LevelManager::PLAYABLE:
            return showPlayableLayer_ = !showPlayableLayer_;
        case LevelManager::FOREGROUND:
            return showForegroundLayer_ = !showForegroundLayer_;
        case LevelManager::BACKGROUND:
            return showBackgroundLayer_ = !showBackgroundLayer_;
        }
    }
private:
    GameWindow *window_;
    Viewport viewport_;
    void update_viewport();

    Vector2 cursorPos_ = Vector2(0, 0);
    Vector2 cursorVelocity_ = Vector2(0, 0);


    char levelName_[MAX_LEVEL_NAME];
    char backgroundPath_[MAX_TEXTURE_PATH];
    char backgroundOverlayPath_[MAX_TEXTURE_PATH];
    char terrainPath_[MAX_TEXTURE_PATH];
    char nextLevel_[MAX_LEVEL_PATH];

    int endGameX_ = 0;
    int backgroundWidth_ = 0;
    int backgroundOverlayWidth_ = 0;
    int bottomY_ = 0;
    int playerX_ = 0;
    int playerY_ = 0;
    int gridSize_ = 1;
    SpriteSheet *background_ = NULL;
    SpriteSheet *backgroundOverlay_ = NULL;
    SpriteSheet *terrain_ = NULL;
    
    std::vector<ObjectData> playableLayer_;
    std::vector<ObjectData> foregroundLayer_;
    std::vector<ObjectData> backgroundLayer_;
    std::vector<ActorData> actors_;
    
    std::vector<ObjectData> *current_layer() {
        switch (currentLayer_) {
        case LevelManager::FOREGROUND:
            return &foregroundLayer_;
        case LevelManager::BACKGROUND:
            return &backgroundLayer_;
        default:
            return &playableLayer_;
        }
    }

    void add_object(std::vector<ObjectData> *, ObjectData);
    void remove_object(std::vector<ObjectData> *, Vector2);
    Vector2 actor_size_for_actor(ActorType type);
    void add_actor(ActorData);
    void remove_actor(Vector2);
    void draw_object(ObjectData);

    bool showPlayableLayer_ = true;
    bool showForegroundLayer_ = true;
    bool showBackgroundLayer_ = true;
    bool isKeyDown_ = false;
    LevelManager::Layer currentLayer_ = LevelManager::PLAYABLE;
    ObjectType currentObjectType_ = BLOCK;
    ActorType currentActorType_ = DOG;
    Texture selectedTexture_ = { 0, 0, 0, 0 };

    SpriteSheet *defaultSpriteSheet_ = SpriteSheet::get("spr/terrain.bmp");
    SpriteSheet *bumperSpriteSheet_ = SpriteSheet::get("spr/Bumper.bmp");
    SpriteSheet *metalGearSpriteSheet_ = SpriteSheet::get("spr/metalgearsheet.bmp");
    SpriteSheet *zeldaEnemiesSpriteSheet_ = SpriteSheet::get("spr/Zelda_Enemies_Sprite.bmp");
    SpriteSheet *marioSpriteSheet_ = SpriteSheet::get("spr/mario.bmp");
};