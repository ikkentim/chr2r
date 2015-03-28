#pragma once

#include <vector>

#include "Vector2.h"
#include "Viewport.h"
#include "Keys.h"
#include "LevelManager.h"

class GameScene;

class GameObject {
public:
    /* Constructors */
    GameObject();
    GameObject(bool isSolid);
	GameObject(Vector2 position, Vector2 size);
    GameObject(bool isSolid, Vector2 pos, Vector2 size);

    /* Getters */
	Vector2 position() const {
		return position_;
	}
	Vector2 velocity() const {
		return velocity_;
	}
	Vector2 size() const {
		return size_;
	}
    bool is_solid() const {
        return isSolid_;
    }
    bool is_on_ground() const {
        return onGround_;
    }
	
    /* Game logic */
    virtual void update(GameScene *, double, Keys) = 0;
	virtual void render(Viewport &) = 0;

    /* Positioning */
    virtual void apply_velocity(double);

    /* Collision */
    bool is_colliding_with(GameObject *, double);
    void check_for_collisions(GameScene *, GameObject**, int, double);
    virtual void entered_collision(GameScene *, GameObject *, Vector2);

    /* state machine */
	void clear_states();
protected:
	Vector2 position_;
    Vector2 velocity_;
    Vector2 size_;
    bool isSolid_ = true;

private:
    bool onGround_ = false;
};