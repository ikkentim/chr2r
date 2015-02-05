#include <windows.h>
#include "Texture.h"
#include "Vector2.h"
#include "Viewport.h"

#pragma once

class SpriteSheet
{
public:
    static SpriteSheet *terrain;
    static SpriteSheet *splash;

    SpriteSheet(HWND, HDC, const char *, COLORREF = RGB(255, 128, 255));
    ~SpriteSheet(void);
    void Draw(Texture &, Vector2 &pos, Viewport &);

private:
    HBITMAP bmpb;
    HWND hWnd;
    HDC	dcBuf, dcImage;
    COLORREF transCol;
};