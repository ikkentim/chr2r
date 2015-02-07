#include "Vector2.h"
#include "Viewport.h"
#include "Keys.h"

#pragma once

class GameObject {
public:
    GameObject();
    GameObject(Vector2 position, Vector2 size);
    Vector2 Position() const {
        return position_;
    }
    virtual void Update(float, Keys) = 0;
	virtual void Render(Viewport &) = 0;
	bool CollidesWith(GameObject *, Vector2 &);
	virtual void EnteredCollision(GameObject *, Vector2 &);

protected:
	Vector2 position_;
	Vector2 size_ = { 0, 0 };
};