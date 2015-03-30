#pragma once

#include <windows.h>

class Window {
public:
	 Window();
	 HRESULT create();
	 int run();
     virtual LRESULT msg_proc(HWND, UINT, WPARAM, LPARAM);

protected:
     virtual void game_init() = 0;
     virtual bool game_loop(double) = 0;
     virtual void game_end() = 0;

	static HINSTANCE instance_;
	HWND  hWnd_;

 	DWORD dwCreationFlags_;
	TCHAR *strWindowTitle_;
	HICON hIcon_;
    HACCEL hAccelTable_;
    HDC graphics_;
private:
	HDC dc_;
	HBITMAP bitmap_;
	HANDLE oldHandle_;
	RECT drawRect_;

};
