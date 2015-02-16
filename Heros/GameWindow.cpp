#include "GameWindow.h"
#include <typeinfo>

#include "SpriteSheet.h"
#include "SplashScene.h"
#include "GameScene.h"
#include "LevelManager.h"
#include <string>

GameWindow::GameWindow() {
}

GameWindow::~GameWindow() {
    if (scene_)
        delete scene_;
}

void GameWindow::UpdateScene(Scene *scene) {
	if (scene_){
		delete scene_;
	}

	scene_ = scene;
	scene_->Start();
}

irrklang::ISoundEngine *GameWindow::SoundEngine() {
	return soundEngine_;
}

void GameWindow::GameInit() {
    SpriteSheet::SetWindow(hWnd_, graphics_);

    soundEngine_ = irrklang::createIrrKlangDevice(); 
    assert(soundEngine_ && "Sound engine failed to load (missing resources?)");
    soundEngine_->setSoundVolume(0.3f);/* Master Volume. */

    scene_ = new SplashScene(this);
	scene_->Start();

    DEVMODE mode;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

    int refresh_rate = mode.dmDisplayFrequency;
    if (refresh_rate < 30)
        refresh_rate = 30;
    frameInterval_ = 1.0f / refresh_rate;
}

void GameWindow::GameEnd() {
    SpriteSheet::Unload();
    soundEngine_->drop();
}

bool GameWindow::GameLoop(double delta) {
	/* Check whether it is time to render another frame. */
    timeSinceRender_ += delta;

    if (timeSinceRender_ >= frameInterval_) {
        timeSinceRender_ -= frameInterval_;

        scene_->Render(delta);
        fps.Update();

#ifdef SHOW_FPS
        TCHAR buf[16];
        sprintf_s(buf, "FPS: %d", fps.GetFps());
        TextOut(graphics_, 5, 5, buf, strlen(buf));

        sprintf_s(buf, "UPS: %d", ups.GetFps());
        TextOut(graphics_, 5, 25, buf, strlen(buf));
#endif
        /* Tell the window to repaint. */
        return true;
    }
	else {
		/* Handle key presses. */
#define MAP_KEY(vk,map); if(GetAsyncKeyState(vk)) { \
	keys_ |= map; } else if (keys_ & map) { \
	keys_ ^= map; }

		MAP_KEY(VK_LEFT, KEY_LEFT);
		MAP_KEY(VK_RIGHT, KEY_RIGHT);
		MAP_KEY(VK_UP, KEY_UP);
		MAP_KEY(VK_DOWN, KEY_DOWN);
		MAP_KEY(VK_SPACE, KEY_JUMP);

#undef MAP_KEY

		/* Simple statement for using ESCAPE to exit. If LSHIFT or LCONTROL is
		* pressed, ESCAPE won't close the window.
		*/

		if (::GetAsyncKeyState(VK_ESCAPE)
			&& !GetAsyncKeyState(VK_LSHIFT)
			&& !GetAsyncKeyState(VK_LCONTROL))
			::exit(0);

		/* This restart button leaks pretty badly but it's useful. */
		if (::GetAsyncKeyState(VK_F5)) {
            soundEngine_->stopAllSounds();

			/* FIXME: Fix leak in LevelManager. (initializer/destructor) */
			while (::GetAsyncKeyState(VK_F5));
			UpdateScene(new GameScene(this));
		}

		scene_->Update(delta, keys_);
		ups.Update();

        return false;
    }
}