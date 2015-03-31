#pragma once
#include "Characters.h"
#include "JumpAbility.h"
#include "SprintAbility.h"
#include "SplashAbility.h"
#include "SneakAbility.h"

#define ANIMATION_INTERVAL	(0.08)

Mario::Mario(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::get("spr/mario.bmp");
    ability = new JumpAbility;
	dialog.push_back(DialogLine(false, "Hi im Mario"));
	dialog.push_back(DialogLine(true, "Hey there"));
	dialog.push_back(DialogLine(false, "It looks like you are stuck"));
	dialog.push_back(DialogLine(true, "Ehh, maybe..."));
	dialog.push_back(DialogLine(true, "..."));
	dialog.push_back(DialogLine(false, "Have you tried jumping?"));
	dialog.push_back(DialogLine(true, "Jumping?"));
	dialog.push_back(DialogLine(false, "Yes, pressing the spacebar?"));
	dialog.push_back(DialogLine(true, "Is that how that works?"));
	dialog.push_back(DialogLine(true, "Convenient, Thanks!"));

}

void Mario::render(Viewport &vp) {
	Texture texture = {
		91, 0,
		16, 28
	};

	spriteSheet_->draw(texture, position_, vp);
}

void Mario::update(GameScene* scene , double delta , Keys keys) {
	Character::update(scene, delta, keys);
}
Sanic::Sanic(Vector2 vect) :Character(vect, Vector2(16, 28)) {
    spriteSheet_ = SpriteSheet::get("spr/sonic_sheet.bmp");
	ability = new SprintAbility;
	dialog.push_back(DialogLine(false, "Man, you're slow"));
	dialog.push_back(DialogLine(true, "Im not slow!"));
	dialog.push_back(DialogLine(false, "Yes you are, try this"));
	dialog.push_back(DialogLine(false, "Press the n key"));
	dialog.push_back(DialogLine(true, "Gotta go fast, Thanks!"));
}

void Sanic::render(Viewport &vp) {
	Texture texture = {
		391, 56,
		34, 40
	};

	spriteSheet_->draw(texture, position_, vp);
}
void Sanic::update(GameScene* scene, double delta, Keys keys) {
	Character::update(scene, delta, keys);
}

Magikarp::Magikarp(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::get("spr/magikarp_Sprite.bmp");
	ability = new SplashAbility;
	dialog.push_back(DialogLine(false, "Magi Magikarp !! "));
	dialog.push_back(DialogLine(true, "Hey ! Humm Nice to meet you"));
	dialog.push_back(DialogLine(false, "Magi Magi Magikarp"));
	dialog.push_back(DialogLine(true, "Certainly, Sir, Myah"));
	dialog.push_back(DialogLine(false, "Magikarp (Use SplashAttack !!!)"));
	dialog.push_back(DialogLine(false, "Magi (Press the S key)"));
	dialog.push_back(DialogLine(true, "Uhh, thanks i guess..."));
}

void Magikarp::render(Viewport &vp) {
	Texture texture = {
		10, 158,
		texture_top, texture_left
	};

	int idx = animationIndex_ > 2
		? animationFrames_ - (2 * (animationIndex_ % animationFrames_) + 2)
		: animationIndex_;

	texture.top += idx * texture_top;

	spriteSheet_->draw(texture, position_, vp);
}

void Magikarp::update(GameScene* scene, double delta, Keys keys) {
	Character::update(scene, delta, keys);
	
	if (animationTime_ >= ANIMATION_INTERVAL) {
		animationTime_ -= ANIMATION_INTERVAL;
		int available_frames = animationFrames_ > 2
			? animationFrames_ * 2 - 2
			: animationFrames_;
		
		animationIndex_ = (animationIndex_ + 1) % available_frames;
	}
}


//Snake
Snake::Snake(Vector2 vect) :Character(vect, Vector2(16, 28)) {
	spriteSheet_ = SpriteSheet::get("spr/Box_Sprite.bmp");
	ability = new SneakAbility;
	dialog.push_back(DialogLine(false, ". . ."));
	dialog.push_back(DialogLine(true, "What the ..!"));
	dialog.push_back(DialogLine(false, "Sshhhhh don't say a word"));
	dialog.push_back(DialogLine(false, "Who are you ?"));
	dialog.push_back(DialogLine(true, "Name Snake"));
	dialog.push_back(DialogLine(true, "What are you doing ?"));
	dialog.push_back(DialogLine(true, "Stop talking take this box could save your life"));
	dialog.push_back(DialogLine(true, "Thanks I guess"));
	dialog.push_back(DialogLine(true, "Press B to hide it will save your life"));
}

void Snake::render(Viewport &vp) {
	Texture texture = {
		76, 12,
		18, 18
	};

	spriteSheet_->draw(texture, position_, vp);
}
void Snake::update(GameScene* scene, double delta, Keys keys) {
	Character::update(scene, delta, keys);
}
