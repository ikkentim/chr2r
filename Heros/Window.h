#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
private:
	//HDC dc_;
	//HBITMAP bitmap_;
	//HBITMAP oldBitmap_;

protected:
	static HINSTANCE instance_;
	HWND  hWnd_;

	DWORD posX_;
	DWORD posY_;
	DWORD dwWindowStyle_;
	DWORD dwExWindowStyle_;
 	DWORD dwCreationFlags_;
	DWORD dwCreationHeight_;
	DWORD dwCreationWidth_;
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

#endif
