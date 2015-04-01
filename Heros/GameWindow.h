/**
 * GameWindow.h
 * Declares the GameWindow class.
 */
#pragma once

#include "Window.h"
#include "Keys.h"
#include "IScene.h"
#include <irrKlang.h>
#include "Console.h"
#include "fps.h"

// Represents the game window
class GameWindow : public Window {
public:
    // Default constructor
    GameWindow();

    // Default destructor
	~GameWindow();

    // Changes the visible scene
    void change_scene(IScene *);

    // Gets the sound engine
    irrklang::ISoundEngine *sound_engine();

    // Processes the specified message
    LRESULT msg_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Gets the console
    Console *console() {
        return console_;
    }

    // Toggles the value which indicates whether the fps counter is displayed
    bool toggleDisplayFps() {
        return displayFps_ = !displayFps_;
    }

protected:
    // Contains game initialisation logic 
    void game_init() override;

    // Contains game loop logic 
    bool game_loop(double) override;

    // Contains game end logic 
    void game_end() override;

private:
    irrklang::ISoundEngine *soundEngine_;
    float frameInterval_ = 0.1f;
    double timeSinceRender_ = 0;
    bool hasJoystick_ = false;
    bool displayFps_ = false;
    IScene *scene_ = NULL;
    Console *console_;
	Keys keys_ = KEY_NONE;
    Keys joystickKeys_ = KEY_NONE;
    Fps ups;
	Fps fps;
};