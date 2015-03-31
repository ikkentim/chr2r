/**
 * GameObject.h
 * Declares the abstract GameObject class.
 */
#pragma once

#include <vector>

#include "Vector2.h"
#include "Viewport.h"
#include "Keys.h"
#include "LevelManager.h"

class GameScene;

// Contains method declarations and method for a game object.
class GameObject {
public:
    // Default constructor
    GameObject();

    // A constructor which sets whether this game object is solid
    GameObject(bool isSolid);

    // A constructor which sets the position and size of the game object
    GameObject(Vector2 position, Vector2 size);

    // A constructor which sets whether this game object is solid and the
    // position and size of this game object
    GameObject(bool isSolid, Vector2 pos, Vector2 size);

    // Gets the position
	Vector2 position() const {
		return position_;
	}

    // Gets the velocity
	Vector2 velocity() const {
		return velocity_;
	}

    // Gets the size
	Vector2 size() const {
		return size_;
	}

    // Gets a value indicating whether the game object is solid
    bool is_solid() const {
        return isSolid_;
    }
    // Gets a value indicating whether the game object is on the ground
    bool is_on_ground() const {
        return onGround_;
    }

    // Performs the update logic
    virtual void update(GameScene *scene, double delta, Keys keys) = 0;

    // Renders the graphics
	virtual void render(Viewport &viewport) = 0;

    // Applies the current velocity to the position
    virtual void apply_velocity(double delta);

    // Gets a value indicating whether the game object is colliding with the
    // specified other game object
    bool is_colliding_with(GameObject * other, double delta);

    // Checks for collisions with the specified array of game objects and
    // corrects the position and velocity
    void check_for_collisions(GameScene *scene, GameObject **others, int count,
        double delta);

    // Contains logic for handling collisions
    virtual void entered_collision(GameScene *scene, GameObject *other, 
        Vector2 overlap);
protected:
	Vector2 position_;
    Vector2 velocity_;
    Vector2 size_;
    bool isSolid_ = true;

private:
    bool onGround_ = false;
};