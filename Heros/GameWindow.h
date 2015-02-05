#include "Window.h"
#include "Keys.h"
#include "Scene.h"

#pragma once

class GameWindow : public Window {
public:
    GameWindow();
	~GameWindow();

    void UpdateScene(Scene *);
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:
    void GameInit();
    void GameLoop(float);
    void GameEnd();

private:
    Scene *scene_ = NULL;
    Keys keys_ = KEY_NONE;
};