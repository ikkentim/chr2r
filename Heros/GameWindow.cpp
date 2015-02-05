#include "GameWindow.h"

#include "SpriteSheet.h"
#include "SplashScene.h"

GameWindow::GameWindow() {
}

GameWindow::~GameWindow() {
    if (scene_)
        delete scene_;
}

void GameWindow::UpdateScene(Scene *scene) {
    if (scene_)
        delete scene_;
    
    scene_ = scene;
}

void GameWindow::GameInit() {
    SetFPS(60);
    SpriteSheet::terrain = new SpriteSheet(hWnd_, graphics_, "terrain.bmp");
    SpriteSheet::splash = new SpriteSheet(hWnd_, graphics_, "splash.bmp");

    scene_ = new SplashScene(this);
}

void GameWindow::GameEnd() {
    delete SpriteSheet::terrain;
}

void GameWindow::GameLoop(float delta) {
    /* Handle keys */
#define MAP_KEY(vk,map); if(GetAsyncKeyState(vk)) { \
    keys_ |= map; } else if(keys_ & map) { \
    keys_ ^= map; }

    MAP_KEY(VK_LEFT, KEY_LEFT);
    MAP_KEY(VK_RIGHT, KEY_RIGHT);
    MAP_KEY(VK_SPACE, KEY_JUMP);

#undef MAP_KEY

    if (::GetAsyncKeyState(VK_ESCAPE) && !GetAsyncKeyState(VK_LSHIFT) && !GetAsyncKeyState(VK_LCONTROL))
        if (::MessageBox(NULL, "Quit Game?", "Hero", MB_YESNO) == IDYES)
            ::exit(0);

    if (scene_)
        scene_->Update(delta, keys_);
}

LRESULT GameWindow::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return Window::MsgProc(hWnd, uMsg, wParam, lParam);
}

