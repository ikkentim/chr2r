#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"

class MenuScene : public Scene {
public:
	MenuScene(GameWindow *);
	virtual ~MenuScene();
	virtual void Start();
	void Update(double, Keys);
    void Render(HDC graphics);

private:
    SpriteSheet *spriteSheet_;
    SpriteSheet *spriteSheetPlay_;
    SpriteSheet *spriteSheetExit_;
    SpriteSheet *spriteSheetArrow_;
	GameWindow *window_;
	int selectedOption_=0;
	double keyDelay_=0;
};