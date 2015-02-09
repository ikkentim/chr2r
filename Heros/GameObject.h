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
    virtual void Update(double, Keys) = 0;
	virtual void Render(Viewport &) = 0;
	virtual void EnteredCollision(GameObject *, Vector2 &);
    virtual void ApplyVelocity(double);

	bool FixCollider(GameObject *);
	bool CheckCollidingVelocity(GameObject *, GameObject *, bool &, bool &);
	bool IsIntersecting(GameObject *, GameObject *);
    bool InRange(GameObject *, double range);

protected:
	Vector2 position_;
	Vector2 velocity_;
	Vector2 size_ = { 0, 0 };
};