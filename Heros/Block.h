#include "GameObject.h"
#include "Texture.h"
#pragma once

class Block : public GameObject {
public:
    Block(Texture);
    Block(Texture, Vector2);
    void Update(float, Keys);
    void Render(Viewport &);
private:
    Texture texture_;
};