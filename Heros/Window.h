#include <windows.h>
#include <chrono>

using namespace std::chrono;

#pragma once

class Window {
public:
	 Window();
	 HRESULT Create();
	 int Run();
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:
    void SetFPS(int);
     virtual void GameInit() = 0;
     virtual void GameLoop(float) = 0;
     virtual void GameEnd() = 0;

	static HINSTANCE instance_;
	HWND  hWnd_;

 	DWORD dwCreationFlags_;
	TCHAR *strWindowTitle_;
	HBRUSH hbrWindowColor_;
	HICON hIcon_;
    HACCEL hAccelTable_;
    HDC graphics_;

    INT64 freq_;
    INT64 start_, stop_;
	milliseconds lastframems_;
    int fps_;
private:
	HDC dc_;
	HBITMAP bitmap_;
	HANDLE oldHandle_;
	RECT drawRect_;

};
