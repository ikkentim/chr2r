#include <stdio.h>
#include "Actor.h"
#include "SpriteSheet.h"

#pragma once

class Ennemis : public Actor {
public:
	Ennemis(Vector2, Vector2);
	~Ennemis();
    void GoLeft(double);
    void GoRight(double);
	void Render(Viewport &);
	void Update(double, Keys);
	

private: 
	bool collision = false;
	bool jump = true;

	

};