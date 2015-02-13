#pragma once

#include <windows.h>
#include "Texture.h"
#include "Vector2.h"
#include "Viewport.h"

#define SPRITE_SHEET_COUNT      (5)

class SpriteSheet
{
public:
    enum Type {
        TERRAIN,
        SPLASH_SCREEN,
        BACKGROUND01,
        MARIO,
		COIN
    };

    static void SetWindow(HWND, HDC);
    static void Unload();
    static SpriteSheet *Get(Type);

    SpriteSheet(const char *);
    ~SpriteSheet(void);
    void Draw(Texture &, Vector2 &pos, Viewport &);
    void Draw(Texture &, int offsetx, int offsety);

private:
    static SpriteSheet *spriteSheets_[SPRITE_SHEET_COUNT];
    static char *spriteFileNames_[SPRITE_SHEET_COUNT];
    static HWND hWnd_;
    static HDC dcBuf_;

    HDC	dcImage_;
};