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
    virtual ~EditorScene();
    virtual void Start();
    void Update(double, Keys);
    void Render(HDC graphics);
    void Save(const char *);

    void SetBackground(const char *background) {
        strcpy_s(backgroundPath_, background);
        background_ = SpriteSheet::Get(background);
    }

    void SetTerrain(const char *terrain) {
        strcpy_s(terrainPath_, terrain);
        terrain_ = SpriteSheet::Get(terrain);
    }

    void SetLevelName(const char *name) {
        strcpy_s(levelName_, name);
    }

    void SetNextLevel(const char *path) {
        strcpy_s(nextLevel_, path);
    }

    void SetBackgroundWidth(int backgroundWidth) {
        backgroundWidth_ = backgroundWidth;
    }

    void SetBottomY(int y) {
        bottomY_ = y;
    }

    void GoTo(int x, int y) {
        cursorPos_.x = x;
        cursorPos_.y = y;
    }

    void SetPlayerSpawn(int x, int y) {
        playerX_ = x;
        playerY_ = y;
    }
    void GetCurrentPos(int &x, int &y) {
        x = ((int)cursorPos_.x / gridSize_) * gridSize_;
        y = ((int)cursorPos_.y / gridSize_) * gridSize_;
    }

    void SetGridSize(int size) {
        gridSize_ = size;
    }

    void SelectTexture(int left, int top, int width, int height) {
        selectedTexture_.left = left;
        selectedTexture_.top = top;
        selectedTexture_.width = width;
        selectedTexture_.height = height;
    }

    bool ToggleLayerVisible(LevelManager::Layer layer) {
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
    void UpdateViewport();

    Vector2 cursorPos_ = Vector2(0, 0);
    Vector2 cursorVelocity_ = Vector2(0, 0);


    char levelName_[MAX_LEVEL_NAME];
    char backgroundPath_[MAX_TEXTURE_PATH];
    char terrainPath_[MAX_TEXTURE_PATH];
    char nextLevel_[MAX_LEVEL_PATH];

    int backgroundWidth_ = 0;
    int bottomY_ = 0;
    int playerX_ = 0;
    int playerY_ = 0;
    int gridSize_ = 1;
    SpriteSheet *background_;
    SpriteSheet *terrain_;
    
    std::vector<ObjectData> playableLayer_;
    std::vector<ObjectData> foregroundLayer_;
    std::vector<ObjectData> backgroundLayer_;
    std::vector<ActorData> actors_;
    
    std::vector<ObjectData> *GetCurrentLayer() {
        switch (currentLayer_) {
        case LevelManager::FOREGROUND:
            return &foregroundLayer_;
        case LevelManager::BACKGROUND:
            return &backgroundLayer_;
        default:
            return &playableLayer_;
        }
    }
    void AddObject(std::vector<ObjectData> *, ObjectData);
    void RemoveObject(std::vector<ObjectData> *, Vector2);
    Vector2 GetActorSize(ActorType type);
    void AddActor(ActorData);
    void RemoveActor(Vector2);
    void DrawObject(ObjectData);
    bool showPlayableLayer_ = true;
    bool showForegroundLayer_ = true;
    bool showBackgroundLayer_ = true;
    bool isKeyDown_ = false;
    LevelManager::Layer currentLayer_ = LevelManager::PLAYABLE;
    ObjectType currentObjectType_ = BLOCK;
    ActorType currentActorType_ = DOG;
    Texture selectedTexture_ = { 0, 0, 0, 0 };

    SpriteSheet *defaultSpriteSheet_ = SpriteSheet::Get("spr/terrain.bmp");
    SpriteSheet *bumperSpriteSheet_ = SpriteSheet::Get("spr/Bumper.bmp");
    SpriteSheet *metalGearSpriteSheet_ = SpriteSheet::Get("spr/metalgearsheet.bmp");
    SpriteSheet *zeldaEnemiesSpriteSheet_ = SpriteSheet::Get("spr/Zelda_Enemies_Sprite.bmp");
    SpriteSheet *marioSpriteSheet_ = SpriteSheet::Get("spr/mario.bmp");
};