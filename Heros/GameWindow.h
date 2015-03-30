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

    void change_scene(Scene *);
    irrklang::ISoundEngine *sound_engine();
    LRESULT msg_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    Console *console() {
        return console_;
    }
protected:
    void game_init() override;
    bool game_loop(double) override;
    void game_end() override;

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