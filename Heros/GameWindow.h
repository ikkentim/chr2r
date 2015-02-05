#include "Window.h"
#include "LevelManager.h"
#include "Player.h"
#include "Keys.h"

#pragma once

class GameWindow : public Window
{
public:
    GameWindow();
	~GameWindow();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:
    void GameInit();
    void GameLoop(float);
    void GameEnd();

private:
    HBITMAP *textureMap_;
    LevelManager *level_;
    Player *player_;
    Keys keys_;
};