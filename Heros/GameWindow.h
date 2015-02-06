#include "Window.h"
#include "Keys.h"
#include "Scene.h"
#include <irrKlang.h>

#pragma once

class GameWindow : public Window {
public:
    GameWindow();
	~GameWindow();

    void UpdateScene(Scene *);
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
    irrklang::ISoundEngine *SoundEngine();
protected:
    void GameInit();
    void GameLoop(float);
    void GameEnd();

private:
    irrklang::ISoundEngine *soundEngine_;
    Scene *scene_ = NULL;
    Keys keys_ = KEY_NONE;
};