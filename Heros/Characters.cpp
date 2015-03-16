#pragma once
#include "Characters.h"

Mario::Mario(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::Get("spr/mario.bmp");
	//TODO: ability = jump
	dialog.push_back(DialogLine(true, "Hi im Mario"));
	dialog.push_back(DialogLine(false, "Hey"));
	dialog.push_back(DialogLine(true, "Nice Weather, huh?"));
	dialog.push_back(DialogLine(false, "Certainly, Sir, Myah"));

}

void Mario::Render(Viewport &vp) {
	Texture texture = {
		91, 0,
		16, 28
	};

	spriteSheet_->Draw(texture, position_, vp);
}

void Mario::Update(GameScene* scene , double delta , Keys keys) {
	Character::Update(scene, delta, keys);
}
Sanic::Sanic(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::Get("spr/sonic_sheet.bmp");
	//TODO: ability = jump
	dialog.push_back(DialogLine(true, "Hi There, im Sonic "));
	dialog.push_back(DialogLine(false, "Hey"));
	dialog.push_back(DialogLine(true, "Nice Weather, huh?"));
	dialog.push_back(DialogLine(false, "Certainly, Sir, Myah"));
}

void Sanic::Render(Viewport &vp) {
	Texture texture = {
		391, 56,
		34, 40
	};

	spriteSheet_->Draw(texture, position_, vp);
}
void Sanic::Update(GameScene* scene, double delta, Keys keys) {
	Character::Update(scene, delta, keys);
}