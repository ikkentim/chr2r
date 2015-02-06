#include "GameWindow.h"
#include <typeinfo>

#include "Block.h"
#include "SpriteSheet.h"

GameWindow::GameWindow() {
    keys_ = KEY_NONE;

    /* push basic level */
    level_ = new LevelManager();

	Vector2 player_spawn = { 100, 32 };
	player_ = new Player(player_spawn, Vector2(16, 16));

    Texture grass_top = { 444, 253, 16, 16 };
    for (int x = 0; x < 15; x++) {
        level_->PlayableLayer()->push_back(new Block(grass_top, {16.0f * x, 48.0f}));
	}

	level_->PlayableLayer()->push_back(new Block(grass_top, { 16.0f * 10, 32.0f }));

    level_->PlayableLayer()->push_back(player_);
}

GameWindow::~GameWindow() {
    delete level_;
    delete player_;
}


void GameWindow::GameInit() {
    SetFPS(60);
    SpriteSheet::terrain = new SpriteSheet(hWnd_, graphics_, "terrain.bmp");

	Texture testtex = { 0, 0, 200, 200 };
	Vector2 testvec = { 10, 10 };
	SpriteSheet::terrain->Draw(testtex, testvec);

	InvalidateRect(hWnd_, 0, false);
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

	GameObject *object;
	GameObject *object2;

	/* Check collision on playerlayer */
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		object = *it;

		for (LevelLayer::iterator it2 = layer->begin(); it2 != layer->end(); ++it2) {
			if (it == it2)
				continue;

			object2 = *it2;

			Vector2 overlapping;

			if (object->CollidesWith(object2, overlapping))
			{
				object->EnteredCollision(object2, overlapping);
			}

		}
	}

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

