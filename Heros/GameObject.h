#include "Vector2.h"
#include "Viewport.h"
#include "Keys.h"

#pragma once

class GameObject {
public:
    GameObject();
    GameObject(Vector2);
    Vector2 Position() const {
        return position_;
    }
    virtual void Update(float, Keys) = 0;
    virtual void Render(Viewport &) = 0;


protected:
    Vector2 position_;
};