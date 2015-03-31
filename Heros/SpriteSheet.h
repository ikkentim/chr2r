/**
 * SpriteSheet.h
 * Declares the SpriteSheet class.
 */
#pragma once

#include <string>
#include <map>
#include <windows.h>
#include "Texture.h"
#include "Vector2.h"
#include "Viewport.h"

// Represents a sprite sheet
class SpriteSheet
{
public:
    // Default destructor
    ~SpriteSheet();

    // Sets the window and graphics handle
    static void set_window(HWND, HDC);

    // Unloads all cached sheets
    static void unload();

    // Gets a spritesheet for teh specified path
    static SpriteSheet *get(std::string path);

    // Draw the specified texture
    void draw(Texture &texture, Vector2 &pos, Viewport &viewport);

    // Draw the specified texture
    void draw(Texture &texture, int x, int y);

private:
    SpriteSheet(const char *path);

    typedef std::map<std::string, SpriteSheet *> SpriteMap;
    static SpriteMap spriteSheets_;
    static HWND hWnd_;
    static HDC dcBuf_;

    HDC	dcImage_;
};