#include "SpriteSheet.h"

/* FIXME: Create some kind of spritesheet loading mechanism, 
 * instead of global vars */
SpriteSheet *SpriteSheet::terrain;
SpriteSheet *SpriteSheet::splash;
SpriteSheet *SpriteSheet::background01;
SpriteSheet *SpriteSheet::character;
SpriteSheet *SpriteSheet::mario;
SpriteSheet *SpriteSheet::coin;

SpriteSheet::SpriteSheet(HWND hWnd, HDC dcBuf,
    const char * file,
    COLORREF transCol) {
    this->hWnd = hWnd;
    this->dcBuf = dcBuf;
    this->transCol = transCol;

    HBITMAP bitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    
    assert(bitmap && "Bitmap cannot be loaded (asset missing?)");

    dcImage = CreateCompatibleDC(dcBuf);
    (HBITMAP)SelectObject(dcImage, bitmap);

    GetObject(dcImage, sizeof(bitmap), &bitmap);
}

SpriteSheet::~SpriteSheet(void) {
    ::ReleaseDC(hWnd, dcImage);
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
    int x = (int)pos.x - vp.x - texture.width / 2;
    int y = (int)pos.y - vp.y - texture.height / 2;

    Draw(texture, x, y);
}

void SpriteSheet::Draw(Texture &texture, int x, int y) {
    TransparentBlt(dcBuf,
        x, y,
        texture.width, texture.height, dcImage,
        texture.left, texture.top,
        texture.width, texture.height, transCol);
}