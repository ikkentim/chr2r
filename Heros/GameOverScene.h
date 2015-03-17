#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"
class GameOverScene : public Scene {
public:
	GameOverScene(GameWindow *);
	virtual ~GameOverScene();
	virtual void Start();
	void Update(double, Keys);
	void Render(HDC graphics);
private:
	SpriteSheet *spriteSheet_;
	double position_;

	GameWindow *window_;

	double time_ = 0;
};