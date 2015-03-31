/**
* main.cpp
* The main entry point of the application.
*/

#include "GameWindow.h"

// The main entry point of the application.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    GameWindow app;

    if (!app.create())
        return 0;

    return app.run();
}