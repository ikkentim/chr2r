#pragma once
#include "Characters.h"

Mario::Mario(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::Get("spr/mario.bmp");
	//TODO: ability = jump
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
	spriteSheet_ = SpriteSheet::Get("spr/mario.bmp");
	//TODO: ability = jump
}

void Sanic::Render(Viewport &vp) {
	Texture texture = {
		91, 0,
		16, 28
	};

	spriteSheet_->Draw(texture, position_, vp);
}
void Sanic::Update(GameScene* scene, double delta, Keys keys) {
	Character::Update(scene, delta, keys);
}