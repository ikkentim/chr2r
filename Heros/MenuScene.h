#pragma once

#include "Scene.h"
#include "GameWindow.h"

class MenuScene : public Scene {
public:
	MenuScene(GameWindow *);
	virtual ~MenuScene();
	virtual void Start();
	void Update(double, Keys);
	void Render(double);

private:
	GameWindow *window_;
	int selectedOption_=0;
	double keyDelay_=0;
};