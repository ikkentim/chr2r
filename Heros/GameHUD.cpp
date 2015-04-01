/**
 * GameHUD.cpp
 * Defines the GameHUD class.
 */

#include "GameHUD.h"

void GameHUD::update(GameScene * scene , double delta, Keys keys) {
	lives_ = scene->lives();
    score_ = scene->score();
}
void GameHUD::render(HDC gr) {
	string str = to_string(lives_);

	if (lives_ > 1)
		str.append(" Lives");
	else
		str.append(" Life");

    /*
	SpriteSheet * spr = SpriteSheet::get("spr/mario.bmp");

	Texture txt = {
		308, 48,
		18, 18
	};

	spr->draw(txt, 100, 100);
    */
    TextOut(gr, 550, 10, str.c_str(), str.length());

    char buf[16];
    sprintf_s(buf, "%d", score_);
    TextOut(gr, 10, 458, buf, strlen(buf));
}