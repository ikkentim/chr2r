#pragma once

#include "Scene.h"
#include "GameWindow.h"

class MenuScene : public Scene {
public:
	MenuScene(GameWindow *);
	~MenuScene();
	void Update(double, Keys);
	void Render(double);

private:
	GameWindow(*window_);
};