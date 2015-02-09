#include "GameWindow.h"
#include <typeinfo>

#include "SpriteSheet.h"
#include "SplashScene.h"
#include "LevelManager.h"
#include <string>

#define RENDER_FREQUENCY            (60)

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
    SpriteSheet::terrain = new SpriteSheet(hWnd_, graphics_, "spr/terrain.bmp");
    SpriteSheet::splash = new SpriteSheet(hWnd_, graphics_, "spr/splash.bmp");
    SpriteSheet::background01 = new SpriteSheet(hWnd_, graphics_, "spr/background01.bmp");
	SpriteSheet::character = new SpriteSheet(hWnd_, graphics_, "spr/DocChar.bmp");

    soundEngine_ = irrklang::createIrrKlangDevice();

    if (!soundEngine_)
        return;

    scene_ = new SplashScene(this);
}

void GameWindow::GameEnd() {
    delete SpriteSheet::terrain;
    delete SpriteSheet::splash;
    delete SpriteSheet::background01;
	delete SpriteSheet::character;

    soundEngine_->drop();
}

bool GameWindow::GameLoop(double delta) {

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
    ups.Update();

    timeSinceRender_ += delta;

    if (timeSinceRender_ >= (1.0f / RENDER_FREQUENCY)) {
        timeSinceRender_ -= (1.0f / RENDER_FREQUENCY);

        scene_->Render(delta);
        fps.Update();

#ifdef SHOW_FPS
        TCHAR buf[16];
        std::sprintf(buf, "FPS: %d", fps.GetFps());
        TextOut(graphics_, 5, 5, buf, strlen(buf));

        std::sprintf(buf, "UPS: %d", ups.GetFps());
        TextOut(graphics_, 5, 25, buf, strlen(buf));
#endif
        return true;
    }
    else {
        return false;
    }
}