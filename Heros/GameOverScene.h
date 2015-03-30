#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "SpriteSheet.h"
class GameOverScene : public Scene {
public:
	GameOverScene(GameWindow *);
    ~GameOverScene() override;
    void start() override;
    void update(double, Keys) override;
	void render(HDC graphics) override;

private:
	SpriteSheet *spriteSheet_;
	GameWindow *window_;
	double time_ = 0;
};