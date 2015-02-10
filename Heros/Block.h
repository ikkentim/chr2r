#pragma once

#include "GameObject.h"
#include "Texture.h"

class Block : public GameObject {
public:
    Block(Texture);
    Block(Texture, Vector2);
    void Update(double, Keys) override;
    void Render(Viewport &) override;
private:
    Texture texture_;
};