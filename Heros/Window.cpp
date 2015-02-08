#include "Window.h"
#include <tchar.h>
#include <math.h>

#define WINDOW_WIDTH    (640)
#define WINDOW_HEIGHT   (480)

static Window *window = NULL;
HINSTANCE Window::instance_ = GetModuleHandle(NULL);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return window->MsgProc(hWnd, uMsg, wParam, lParam);
}

Window::Window() {
	window = this;

	this->hWnd_					= NULL;
	this->dwCreationFlags_		= 0L;
	this->dwCreationFlags_		= SW_SHOW;
	this->hbrWindowColor_		= (HBRUSH)(COLOR_WINDOW+1);
	this->hIcon_				= LoadIcon(instance_, (LPCTSTR)IDI_APPLICATION);
	this->strWindowTitle_		= _T("Heros");

    ::QueryPerformanceFrequency((LARGE_INTEGER*)&freq_);

    fps_ = (int)freq_;

	lastframems_ = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
}

int Window::Run() {
    MSG msg = { 0 };

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            ::QueryPerformanceCounter((LARGE_INTEGER*)&start_);
            stop_ = start_;

            /*while (stop_ - start_ < freq_ / fps_)
				::QueryPerformanceCounter((LARGE_INTEGER*)&stop_);*/

            Rectangle(graphics_, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

			milliseconds nowms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());

			GameLoop((nowms.count() - lastframems_.count()) / 1000.0f);

			StretchBlt(dc_, drawRect_.left, drawRect_.top, 
				drawRect_.right - drawRect_.left, 
                drawRect_.bottom - drawRect_.top, graphics_, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SRCCOPY);
	        }

		lastframems_ = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
    }

    GameEnd();

	SelectObject(graphics_, oldHandle_);
	DeleteObject(bitmap_);
	DeleteDC(graphics_);

    return msg.wParam;
}

HRESULT Window::Create() {
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

    int window_width = WINDOW_WIDTH;
    int window_height = WINDOW_HEIGHT;

#ifdef FULLSCREEN_MODE
	HMONITOR hmon = MonitorFromWindow(hWnd_,
		MONITOR_DEFAULTTONEAREST);

	MONITORINFO monitor = { sizeof(monitor) };

	if (!GetMonitorInfo(hmon, &monitor)) return false;

	hWnd_ = ::CreateWindowEx(0, _T("Skeleton"), strWindowTitle_, WS_POPUP | WS_VISIBLE,
		monitor.rcMonitor.left,
		monitor.rcMonitor.top,
		monitor.rcMonitor.right - monitor.rcMonitor.left,
		monitor.rcMonitor.bottom - monitor.rcMonitor.top,
	  NULL, NULL, instance_, NULL);

	window_width = monitor.rcMonitor.right - monitor.rcMonitor.left;
	window_height = monitor.rcMonitor.bottom - monitor.rcMonitor.top;
#else

    RECT winSz = { 0, 0, window_width, window_height };
    AdjustWindowRect(&winSz, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, false);

    hWnd_ = ::CreateWindowEx(0, _T("Skeleton"), strWindowTitle_, 
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX ^ WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
        winSz.right - winSz.left,
        winSz.bottom - winSz.top,
		NULL, NULL, instance_, NULL);
#endif /* FULLSCREEN_MODE */

    float hScale = (float)window_width / WINDOW_WIDTH;
    float vScale = (float)window_height / WINDOW_HEIGHT;
	float scale = hScale < vScale ? hScale : vScale;

	int width = (int)floor(640.0f * scale);
	int height = (int)floor(480.0f * scale);

	int hOffset = (window_width - width) / 2;
	int vOffset = (window_height - height) / 2;

	drawRect_ = {
		hOffset, vOffset,
		window_width - hOffset,
		window_height - vOffset
	};

	if (!hWnd_) return false;

	dc_ = ::GetDC(hWnd_);

	graphics_ = CreateCompatibleDC(dc_);
    bitmap_ = CreateCompatibleBitmap(dc_, WINDOW_WIDTH, WINDOW_HEIGHT);
	oldHandle_ = SelectObject(graphics_, bitmap_);

	/* Clear whitespace to black.
     */
	HBRUSH brush = CreateSolidBrush(0);
	SelectObject(dc_, brush);
	Rectangle(dc_, 0, 0, window_width, window_height);

	SelectObject(graphics_, CreatePen(PS_NULL, 0, 0));
	SelectObject(graphics_, CreateSolidBrush(0xffffff));

    GameInit();

	::ShowWindow(hWnd_, dwCreationFlags_);
	::UpdateWindow(hWnd_);

	return true;
}

LRESULT Window::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (!hWnd_)
		hWnd_ = hWnd;

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
   return 0;
}

void Window::SetFPS(int fps) {
    if (fps > 0 && fps < freq_)
        this->fps_ = fps;
}
