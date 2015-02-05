#include "SpriteSheet.h"

SpriteSheet *SpriteSheet::terrain;

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

void SpriteSheet::Draw(Texture &texture, Vector2 &pos) {
	TransparentBlt(dcBuf,
		pos.x, pos.y,
		texture.width, texture.height, dcImage,

		texture.left, texture.top,
		texture.width, texture.height, transCol);
}