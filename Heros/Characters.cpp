#pragma once
#include "Characters.h"
#define ANIMATION_INTERVAL	(0.08)

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

Magikarp::Magikarp(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::Get("spr/magikarp_Sprite.bmp");
	//TODO: ability = jump
	dialog.push_back(DialogLine(true, "Magi Magikarp !! "));
	dialog.push_back(DialogLine(false, "Hey ! Humm Nice to meet you"));
	dialog.push_back(DialogLine(true, "Magi Magi Magikarp"));
	dialog.push_back(DialogLine(false, "Certainly, Sir, Myah"));
	dialog.push_back(DialogLine(true, "Magikarp (Use SplashAttack !!!)"));
}

void Magikarp::Render(Viewport &vp) {
	Texture texture = {
		10, 158,
		texture_top, texture_left
	};

	int idx = animationIndex_ > 2
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	texture.top += idx * texture_top;

	spriteSheet_->Draw(texture, position_, vp);
}

void Magikarp::Update(GameScene* scene, double delta, Keys keys) {
	Character::Update(scene, delta, keys);
	
	if (animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;
		int available_frames = animationFrames_ > 2
			? animationFrames_ * 2 - 2
			: animationFrames_;
		
		animationIndex_ = (animationIndex_ + 1) % available_frames;
	}
}