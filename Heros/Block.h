#pragma once

#include "GameObject.h"
#include "Texture.h"

class Block : public GameObject {
public:
    Block(SpriteSheet *, Texture);
    Block(SpriteSheet *, Texture, Vector2);
    void Update(GameScene *, double, Keys) override;
    void Render(Viewport &) override;
private:
    SpriteSheet *spriteSheet_;
    Texture texture_;
};