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
    SpriteSheet(const char *);
    ~SpriteSheet(void);

    static void set_window(HWND, HDC);
    static void unload();
    static SpriteSheet *get(std::string);

    void draw(Texture &, Vector2 &pos, Viewport &);
    void draw(Texture &, int offsetx, int offsety);

private:
    typedef std::map<std::string, SpriteSheet *> SpriteMap;
    static SpriteMap spriteSheets_;
    static HWND hWnd_;
    static HDC dcBuf_;

    HDC	dcImage_;
};