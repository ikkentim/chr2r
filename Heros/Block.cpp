#include "Block.h"
#include "SpriteSheet.h"

Block::Block(Texture tex) :texture_(tex), GameObject() {
}

Block::Block(Texture tex, Vector2 pos) : texture_(tex), GameObject(pos,	Vector2(tex.width, tex.height)) {
	
}

void Block::Update(double delta, Keys keys) {
    /* TODO: update mechanism */
}

void Block::Render(Viewport &vp) {
    SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(texture_, position_, vp);
}