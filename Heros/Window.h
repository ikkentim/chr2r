#pragma once

#include <windows.h>

class Window {
public:
	 Window();
	 HRESULT Create();
	 int Run();
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:
     virtual void GameInit() = 0;
     virtual bool GameLoop(double) = 0;
     virtual void GameEnd() = 0;

	static HINSTANCE instance_;
	HWND  hWnd_;

 	DWORD dwCreationFlags_;
	TCHAR *strWindowTitle_;
	HBRUSH hbrWindowColor_;
	HICON hIcon_;
    HACCEL hAccelTable_;
    HDC graphics_;
private:
	HDC dc_;
	HBITMAP bitmap_;
	HANDLE oldHandle_;
	RECT drawRect_;

};
