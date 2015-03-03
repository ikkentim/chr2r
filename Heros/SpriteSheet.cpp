#include "SpriteSheet.h"

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
	
};

HWND SpriteSheet::hWnd_;
HDC SpriteSheet::dcBuf_;

void SpriteSheet::SetWindow(HWND hWnd, HDC dcBuf) {
    hWnd_ = hWnd;
    dcBuf_ = dcBuf;
}

SpriteSheet *SpriteSheet::Get(Type type) {
    if (!spriteSheets_[type]) {
        spriteSheets_[type] = new SpriteSheet(spriteFileNames_[type]);
    }

    return spriteSheets_[type];
}

void SpriteSheet::Unload() {
    for (int i = 0; i < SPRITE_SHEET_COUNT; i++) {
        if (spriteSheets_[i]) {
            delete spriteSheets_[i];
        }
    }
}
SpriteSheet::SpriteSheet(const char * file) {
    HBITMAP bitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    
    assert(bitmap && "Bitmap cannot be loaded (asset missing?)");

    dcImage_ = CreateCompatibleDC(dcBuf_);
    (HBITMAP)SelectObject(dcImage_, bitmap);

    GetObject(dcImage_, sizeof(bitmap), &bitmap);
}

SpriteSheet::~SpriteSheet(void) {
    ::ReleaseDC(hWnd_, dcImage_);
}

void SpriteSheet::Draw(Texture &texture, Vector2 &pos, Viewport &vp) {
	Vector2 offset = pos - vp.Position();

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
    int x = floor(pos.x) - vp.x - texture.width / 2;
    int y = floor(pos.y) - vp.y - texture.height / 2;

    Draw(texture, x, y);
}

void SpriteSheet::Draw(Texture &texture, int x, int y) {
    TransparentBlt(dcBuf_, x, y,
        texture.width, texture.height, dcImage_,
        texture.left, texture.top,
        texture.width, texture.height, 0xFF80FF);
}