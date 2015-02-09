#include "SpriteSheet.h"

/* FIXME: Create some kind of spritesheet loading mechanism, 
 * instead of global vars */
SpriteSheet *SpriteSheet::terrain;
SpriteSheet *SpriteSheet::splash;
SpriteSheet *SpriteSheet::background01;
SpriteSheet *SpriteSheet::character;

SpriteSheet::SpriteSheet(HWND hWnd, HDC dcBuf,
    const char * file,
    COLORREF transCol) {
    this->hWnd = hWnd;
    this->dcBuf = dcBuf;
    this->transCol = transCol;

    HBITMAP bitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    
    assert(bitmap);

    dcImage = CreateCompatibleDC(dcBuf);
    (HBITMAP)SelectObject(dcImage, bitmap);

    GetObject(dcImage, sizeof(bitmap), &bitmap);
}

SpriteSheet::~SpriteSheet(void) {
    ::ReleaseDC(hWnd, dcImage);
}

void SpriteSheet::Draw(Texture &texture, Vector2 &pos, Viewport &vp) {
	Vector2 offset = pos - vp.Position();

	if (offset.x < -texture.width || offset.y < -texture.height ||
		offset.x > vp.width || offset.y > vp.height) 
        return;

    int x = (int)pos.x - vp.x;
    int y = (int)pos.y - vp.y;
	TransparentBlt(dcBuf,
		x, y,
		texture.width, texture.height, dcImage,
		texture.left, texture.top,
		texture.width, texture.height, transCol);
}