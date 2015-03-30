#include "GameWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    GameWindow app;

    if (!app.create())
        return 0;

    return app.run();
}