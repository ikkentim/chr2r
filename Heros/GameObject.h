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
	Vector2 Velocity() const {
		return velocity_;
	}
	Vector2 Size() const {
		return size_;
	}
    virtual void Update(float, Keys) = 0;
	virtual void Render(Viewport &) = 0;
	bool CollidesWith(GameObject *, Vector2 &);
	virtual void EnteredCollision(GameObject *, Vector2 &);
	virtual void ApplyVelocity();
	bool IsIntersecting(GameObject *, GameObject *, bool &, bool &);

protected:
	Vector2 position_;
	Vector2 velocity_;
	Vector2 size_ = { 0, 0 };
};