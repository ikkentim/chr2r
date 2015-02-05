#include "GameWindow.h"

#include "Block.h"
#include "SpriteSheet.h"

GameWindow::GameWindow() {
    keys_ = KEY_NONE;

    /* push basic level */
    level_ = new LevelManager();

    Vector2 player_spawn = { 64, 48 };
    player_ = new Player(player_spawn);


	Vector2 Ennemis_spawn = {80, 50};
	ennemis_ = new Ennemis{ Ennemis_spawn };

    Texture grass_top = { 444, 253, 16, 16 };
    for (int x = 0; x < 15; x++) {
        level_->PlayableLayer()->push_back(new Block(grass_top, {16.0f * x, 256.0f}));
    }

    level_->PlayableLayer()->push_back(player_);
	level_->PlayableLayer()->push_back(ennemis_);
}

GameWindow::~GameWindow() {
    delete level_;
    delete player_;
}


void GameWindow::GameInit() {
    SetFPS(60);
    SpriteSheet::terrain = new SpriteSheet(hWnd_, graphics_, "terrain.bmp");
}

void GameWindow::GameEnd() {
    delete SpriteSheet::terrain;
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

    if (::GetAsyncKeyState(VK_ESCAPE))
        if (::MessageBox(NULL, "Quit Game?", "Hero", MB_YESNO) == IDYES)
            ::exit(0);

	
    LevelLayer *layer = level_->PlayableLayer();

    /* Update all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;

        object->Update(delta, keys_);
    }

    /* Render all layers */
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;

        /* TODO: Pass viewport to render() */
        object->Render();
    }
	

}

LRESULT GameWindow::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return Window::MsgProc(hWnd, uMsg, wParam, lParam);
}

