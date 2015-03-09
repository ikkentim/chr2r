#include "Block.h"
#include "SpriteSheet.h"

Block::Block(SpriteSheet *spriteSheet, Texture tex) 
    :spriteSheet_(spriteSheet), texture_(tex), GameObject() {
}

Block::Block(SpriteSheet *spriteSheet, Texture tex, Vector2 pos) 
    :spriteSheet_(spriteSheet), texture_(tex), GameObject(pos, Vector2(tex.width, tex.height)) {
	
}

void Block::Update(GameScene *scene, double delta, Keys keys) {
    /* nothing to update. */
}

void Block::Render(Viewport &vp) {
    spriteSheet_->Draw(texture_, position_, vp);
}