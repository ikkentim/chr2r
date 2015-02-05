#include <windows.h>

#pragma once

class Window
{
private:
	HDC dc_;
	HBITMAP bitmap_;
	HANDLE oldHandle_;
	RECT drawRect_;

protected:
	static HINSTANCE instance_;
	HWND  hWnd_;

 	DWORD dwCreationFlags_;
	TCHAR *strWindowTitle_;
	HBRUSH hbrWindowColor_;
	HICON hIcon_;
	HMENU hMenu_;
    HACCEL hAccelTable_;
    HDC graphics_;

    INT64 freq_;
    INT64 start_, stop_;
    int fps_;

public:
	 Window();
	 HRESULT Create();
	 int Run();
	 virtual ~Window();
     virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

protected:   
    void SetFPS(int);

     virtual void GameInit() = 0;
     virtual void GameLoop(float) = 0;
     virtual void GameEnd() = 0;
};
