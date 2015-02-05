#include "Block.h"
#include "SpriteSheet.h"

Block::Block(Texture tex) :texture_(tex), GameObject() {
}

Block::Block(Texture tex, Vector2 pos) : texture_(tex), GameObject(pos) {
}

void Block::Update(float delta, Keys keys) {
    /* TODO: update mechanism */
}

void Block::Render(Viewport &vp) {
    SpriteSheet::terrain->Draw(texture_, position_, vp);
}