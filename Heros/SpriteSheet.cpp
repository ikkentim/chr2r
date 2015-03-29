#include "SpriteSheet.h"
/*
SpriteSheet *SpriteSheet::spriteSheets_[SPRITE_SHEET_COUNT];
char *SpriteSheet::spriteFileNames_[SPRITE_SHEET_COUNT] = {
    "spr/terrain.bmp",
    "spr/splash.bmp",
    "spr/background01.bmp",
    "spr/MainCharacter.bmp",
	"spr/metalgearsheet.bmp",
	"spr/menu.bmp",
	"spr/play_button.bmp",
	"spr/options_button.bmp",
	"spr/exit_button.bmp",
	"spr/arrow_button.bmp",
	"spr/Zelda_Enemies_Sprite.bmp",
	"spr/mario.bmp",
	
};*/

SpriteSheet::SpriteMap SpriteSheet::spriteSheets_;
HWND SpriteSheet::hWnd_;
HDC SpriteSheet::dcBuf_;

void SpriteSheet::set_window(HWND hWnd, HDC dcBuf) {
    hWnd_ = hWnd;
    dcBuf_ = dcBuf;
}

SpriteSheet *SpriteSheet::get(std::string sheet) {
    if (spriteSheets_.find(sheet) != spriteSheets_.end()) {
        return spriteSheets_[sheet];
    }
    else {
        auto sh = new SpriteSheet(sheet.c_str());
        spriteSheets_[sheet] = sh;
        return sh;
    }
}

void SpriteSheet::unload() {
    for(auto kv : spriteSheets_) {
        delete kv.second;
    }

    spriteSheets_.clear();
}
SpriteSheet::SpriteSheet(const char * file) {
    HBITMAP bitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    
#ifdef _DEBUG
    if (!bitmap) {
        char buffer[256];
        sprintf_s(buffer, "\n\n********************\nMissing texture: %s\n********************\n\n", file);
        OutputDebugString(buffer);
    }
#endif
    assert(bitmap && "Bitmap cannot be loaded (asset missing?)");

    dcImage_ = CreateCompatibleDC(dcBuf_);
    (HBITMAP)SelectObject(dcImage_, bitmap);

    GetObject(dcImage_, sizeof(bitmap), &bitmap);
}

SpriteSheet::~SpriteSheet(void) {
    ::ReleaseDC(hWnd_, dcImage_);
}

void SpriteSheet::draw(Texture &texture, Vector2 &pos, Viewport &vp) {
	Vector2 offset = pos - vp.position();

    /* Don't draw if outside of viewport */
    if (offset.x < -texture.width / 2
        || offset.y < -texture.height / 2
        || offset.x > vp.width + texture.height / 2
        || offset.y > vp.height + texture.height / 2) {
        return;
    }

    /* Shift the drawing location by half the texture size.
     * The given position is the center of the object.
     */
    int x = (int)floor(pos.x) - vp.x - texture.width / 2;
    int y = (int)floor(pos.y) - vp.y - texture.height / 2;

    draw(texture, x, y);
}

void SpriteSheet::draw(Texture &texture, int x, int y) {
    TransparentBlt(dcBuf_, x, y,
        texture.width, texture.height, dcImage_,
        texture.left, texture.top,
        texture.width, texture.height, 0xFF80FF);
}