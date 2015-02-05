#include "Window.h"
#include <tchar.h>

static Window *window = NULL;
HINSTANCE Window::instance_ = GetModuleHandle(NULL);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return window->MsgProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
	window = this;

	this->hWnd_					= NULL;
	this->dwCreationFlags_		= 0L;
	this->dwWindowStyle_		= WS_OVERLAPPEDWINDOW;
	this->dwExWindowStyle_		= WS_EX_OVERLAPPEDWINDOW;
	this->dwCreationFlags_		= SW_SHOW;
	this->posX_					= CW_USEDEFAULT;	
	this->posY_					= CW_USEDEFAULT;	
	this->dwCreationWidth_		= CW_USEDEFAULT;
	this->dwCreationHeight_		= CW_USEDEFAULT;
	this->hbrWindowColor_		= (HBRUSH)(COLOR_WINDOW+1);
	this->hIcon_				= LoadIcon(instance_, (LPCTSTR)IDI_APPLICATION);
	this->strWindowTitle_		= _T("Heros");
	this->hMenu_				= NULL; 	

    ::QueryPerformanceFrequency((LARGE_INTEGER*)&freq_);

    fps_ = freq_;
}

Window::~Window()
{
}

int Window::Run()
{
    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            ::QueryPerformanceCounter((LARGE_INTEGER*)&start_);
            stop_ = start_;

            while (stop_ - start_ < freq_ / fps_)
                ::QueryPerformanceCounter((LARGE_INTEGER*)&stop_);

			Rectangle(graphics_, 0, 0, 640, 480);

            GameLoop(1.0f / fps_);

			BitBlt(dc_, 0, 0, 640, 480, graphics_, 0, 0, SRCCOPY);
        }
    }

    GameEnd();

	SelectObject(graphics_, oldHandle_);
	DeleteObject(bitmap_);
	DeleteDC(graphics_);

    return msg.wParam;
}

HRESULT Window::Create()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

    wcex.style          = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= instance_;
	wcex.hIcon			= hIcon_;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= hbrWindowColor_;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _T("Skeleton");
	wcex.hIconSm		= NULL;

	::RegisterClassEx(&wcex);

	RECT winSz = { 0, 0, 640, 480 };
	AdjustWindowRect(&winSz, CS_VREDRAW | CS_HREDRAW, true);

	hWnd_ = ::CreateWindowEx(dwExWindowStyle_,_T("Skeleton"), strWindowTitle_, dwWindowStyle_,
	  posX_, posY_, 
	  winSz.right - winSz.left,
	  winSz.bottom - winSz.top, 
	  NULL, hMenu_, instance_, NULL);

	if (!hWnd_) return false;

	dc_ = ::GetDC(hWnd_);

	graphics_ = CreateCompatibleDC(dc_);
	bitmap_ = CreateCompatibleBitmap(dc_, 640, 480);
	oldHandle_ = SelectObject(graphics_, bitmap_);

    GameInit();

	::ShowWindow(hWnd_, dwCreationFlags_);
	::UpdateWindow(hWnd_);

	return true;

}

LRESULT Window::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!hWnd_)
		hWnd_ = hWnd;

	switch (uMsg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
   return 0;
}

void Window::SetFPS(int fps)
{
    if (fps > 0 && fps < freq_)
        this->fps_ = fps;
}
