#pragma once
#include "Scene.h"
#include <string>
#include "GameWindow.h"
#include "Viewport.h"
#include "SpriteSheet.h"

class EditorScene : public Scene {
public:
    EditorScene(GameWindow *);
    virtual ~EditorScene();
    virtual void Start();
    void Update(double, Keys);
    void Render(HDC graphics);

    void SetBackground(SpriteSheet *background) {
        background_ = background;
    }

    void SetBackgroundWidth(int backgroundWidth) {
        backgroundWidth_ = backgroundWidth;
    }

    void GoTo(int x, int y) {
        cursorPos_.x = x;
        cursorPos_.y = y;
    }
private:
    GameWindow *window_;
    Viewport viewport_;
    void UpdateViewport();

    Vector2 cursorPos_ = Vector2(0, 0);
    Vector2 cursorVelocity_ = Vector2(0, 0);

    int backgroundWidth_ = 0;
    SpriteSheet *background_;
};