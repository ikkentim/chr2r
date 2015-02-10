#pragma once

#include <windows.h>
#include "Texture.h"
#include "Vector2.h"
#include "Viewport.h"

class SpriteSheet
{
public:
    static SpriteSheet *terrain;
    static SpriteSheet *splash;
    static SpriteSheet *background01;
    static SpriteSheet *character;
    static SpriteSheet *mario;

    SpriteSheet(HWND, HDC, const char *, COLORREF = RGB(255, 128, 255));
    ~SpriteSheet(void);
    void Draw(Texture &, Vector2 &pos, Viewport &);
    void Draw(Texture &, int offsetx, int offsety);

private:
    HBITMAP bmpb;
    HWND hWnd;
    HDC	dcBuf, dcImage;
    COLORREF transCol;
};