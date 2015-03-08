#pragma once

#include "Window.h"
#include "Keys.h"
#include "Scene.h"
#include <irrKlang.h>
#include "Console.h"
#include "fps.h"

class GameWindow : public Window {
public:
    GameWindow();
	~GameWindow();

    void UpdateScene(Scene *);
    irrklang::ISoundEngine *SoundEngine();
    LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    Console *console() {
        return console_;
    }
protected:
    void GameInit();
    bool GameLoop(double);
    void GameEnd();

private:
    irrklang::ISoundEngine *soundEngine_;
    float frameInterval_ = 0.1f;
    double timeSinceRender_ = 0;
    bool hasJoystick_ = false;
    Scene *scene_ = NULL;
    Console *console_;
	Keys keys_ = KEY_NONE;
    Keys joystickKeys_ = KEY_NONE;
    Fps ups;
	Fps fps;
};