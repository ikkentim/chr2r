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
#include <map>

#define MAX_GAME_OBJECT_TYPE_NAME_LENGTH  (16)

class EditorScene : public Scene {
public:
    EditorScene(GameWindow *);
    ~EditorScene() override;

    void start() override;
    void update(double, Keys) override;
    void render(HDC graphics) override;
    void load(const char *);
    void save(const char *);

    void background(const char *background);
    void background_overlay(const char *background);
    void terrain(const char *terrain);
    void level_name(const char *name);
    void next_level(const char *path);
    void background_width(int backgroundWidth);
    void background_overlay_width(int backgroundWidth);
    void bottom_y(int y);
    void go_to(int x, int y);
    void end_game_x(int x);
    void player_spawn(int x, int y);
    void current_pos(int &x, int &y);
    void grid_size(int size);
    void select_texture(int left, int top, int width, int height);
    bool toggle_layer_visible(LevelManager::Layer layer);

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
    Vector2 actor_size_for_actor(ActorType type);
    void add_actor(ActorData);
    void remove_actor(Vector2);
    std::vector<ObjectData> *current_layer();

    std::map<ObjectType, GameObjectTypeData> objectTypes_;
    std::map<ActorType, GameObjectTypeData> actorTypes_;

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
    
    bool showPlayableLayer_ = true;
    bool showForegroundLayer_ = true;
    bool showBackgroundLayer_ = true;
    bool isKeyDown_ = false;

    LevelManager::Layer currentLayer_ = LevelManager::PLAYABLE;
    Texture selectedTexture_ = { 0, 0, 0, 0 };
    ObjectType currentObjectType_;
    ActorType currentActorType_;
};