#include "GameWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine,  int nCmdShow) {
	GameWindow app;

	if (!app.Create())
		return 0;
	
	return app.Run();
}