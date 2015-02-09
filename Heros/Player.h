#include "Actor.h"

#pragma once

class Player : public Actor {
public:
	enum STATE{
		GO_RIGHT = 0,
		GO_LEFT,
		JUMP_RIGHT,
		JUMP_LEFT,
		FALL_RIGHT,
		FALL_LEFT,
		DONT_MOVE
	};

    Player(Vector2 position, Vector2 size);
    void Update(float, Keys);
	virtual void EnteredCollision(GameObject *, Vector2 &);
    void Render(Viewport &);

	STATE getState();
	void setState(STATE state);
	
private:
	double animationTime = 0;
	int animationIndex = 0;
	STATE state;

};