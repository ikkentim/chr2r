#include "GameWindow.h"
#include <typeinfo>

#include "SpriteSheet.h"
#include "SplashScene.h"
#include "LevelManager.h"
#include <string>

GameWindow::GameWindow() {
	fps = Fps();
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

irrklang::ISoundEngine *GameWindow::SoundEngine() {
	return soundEngine_;
}

void GameWindow::GameInit() {
    SetFPS(60);
    SpriteSheet::terrain = new SpriteSheet(hWnd_, graphics_, "spr/terrain.bmp");
    SpriteSheet::splash = new SpriteSheet(hWnd_, graphics_, "spr/splash.bmp");
    SpriteSheet::background01 = new SpriteSheet(hWnd_, graphics_, "spr/background01.bmp");

    soundEngine_ = irrklang::createIrrKlangDevice();

    if (!soundEngine_)
        return;

    scene_ = new SplashScene(this);
}

void GameWindow::GameEnd() {
    delete SpriteSheet::terrain;
    delete SpriteSheet::splash;
    delete SpriteSheet::background01;

    soundEngine_->drop();
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

	scene_->Update(delta, keys_);

#ifdef SHOW_FPS
	fps.Update();

	TCHAR buf[8];
	std::sprintf(buf, "%d", fps.GetFps());

	TextOut(graphics_, 10, 10, buf, 3);
#endif
}