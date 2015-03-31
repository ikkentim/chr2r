/**
 * Window.h
 * Declares the abstract Window class.
 */
#pragma once
#include <windows.h>

// Represents an abstract gaming window
class Window {
public:
    // Default constructor
	 Window();

     // Creates the handle
	 HRESULT create();

     // Runs the message loop
	 int run();

     // Processes the specified message
     virtual LRESULT msg_proc(HWND, UINT, WPARAM, LPARAM);

protected:
    // Contains game initialisation logic 
    virtual void game_init() = 0;

    // Contains game loop logic 
    virtual bool game_loop(double) = 0;

    // Contains game end logic 
    virtual void game_end() = 0;

    // The application handle
	static HINSTANCE instance_;

    // The handle
	HWND  hWnd_;

    // The creation flags
 	DWORD dwCreationFlags_;

    // The title
	TCHAR *strWindowTitle_;

    // The icon
	HICON hIcon_;

    // The graphics handle
    HDC graphics_;
private:
	HDC dc_;
	HBITMAP bitmap_;
	HANDLE oldHandle_;
	RECT drawRect_;

};
