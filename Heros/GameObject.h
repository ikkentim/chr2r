#pragma once

#include "Vector2.h"
#include "Viewport.h"
#include "Keys.h"
#include "LevelManager.h"

class GameObject {
public:
    /* Constructors */
    GameObject();
    GameObject(bool isMovable);
	GameObject(Vector2 position, Vector2 size);
    GameObject(bool isMovable, Vector2 pos, Vector2 size);

    /* Getters */
	Vector2 Position() const {
		return position_;
	}
	Vector2 Velocity() const {
		return velocity_;
	}
	Vector2 Size() const {
		return size_;
	}
    bool IsMovable() const {
        return isMovable_;
    }
    bool IsOnGround() const {
        return onGround_;
    }

    /* Game logic */
    virtual void Update(double, Keys) = 0;
	virtual void Render(Viewport &) = 0;

    /* Positioning */
    virtual void ApplyVelocity(double);

    /* Collision */
    bool IsCollidingWith(GameObject *, double);
    void CheckForCollisions(LevelLayer *, double);
	virtual void EnteredCollision(GameObject *);
	double Range(GameObject *);
	bool InRange(GameObject *, int);
protected:
	Vector2 position_;
    Vector2 velocity_;
	Vector2 size_ = { 0, 0 };

private:
    bool onGround_ = false;
    bool isMovable_ = false;
};