#include "GameWindow.h"
#include "LevelManager.h"/* TODO: Remove */

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    LevelManager::write_simple_level();/* TODO: Remove */
    GameWindow app;

    if (!app.create())
        return 0;

    return app.run();
}