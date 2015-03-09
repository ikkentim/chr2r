#pragma once

#include <string>
#include <map>
#include <windows.h>
#include "Texture.h"
#include "Vector2.h"
#include "Viewport.h"

class SpriteSheet
{
public:
    static void SetWindow(HWND, HDC);
    static void Unload();
    static SpriteSheet *Get(std::string);

    SpriteSheet(const char *);
    ~SpriteSheet(void);
    void Draw(Texture &, Vector2 &pos, Viewport &);
    void Draw(Texture &, int offsetx, int offsety);

private:
    typedef std::map<std::string, SpriteSheet *> SpriteMap;
    static SpriteMap spriteSheets_;
    static HWND hWnd_;
    static HDC dcBuf_;

    HDC	dcImage_;
};