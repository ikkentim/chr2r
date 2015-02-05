#include "Window.h"
#include "LevelManager.h"
#include "Player.h"
#include "Keys.h"
#include "Ennemis.h"

#pragma once

class GameWindow : public Window {
public:
    GameWindow();
	~GameWindow();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:
    void GameInit();
    void GameLoop(float);
    void GameEnd();

private:
    LevelManager *level_;
    Player *player_;
    Keys keys_;
	Viewport viewport_;

	Ennemis * ennemis_;
};