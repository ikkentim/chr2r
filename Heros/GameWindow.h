#pragma once

#include "Window.h"
#include "Keys.h"
#include "Scene.h"
#include <irrKlang.h>
#include "fps.h"

class GameWindow : public Window {
public:
    GameWindow();
	~GameWindow();

    void UpdateScene(Scene *);
    irrklang::ISoundEngine *SoundEngine();
protected:
    void GameInit();
    bool GameLoop(double);
    void GameEnd();

private:
    irrklang::ISoundEngine *soundEngine_;
    double timeSinceRender_ = 0;
    Scene *scene_ = NULL;
	Keys keys_ = KEY_NONE;
    Fps ups;
	Fps fps;
};