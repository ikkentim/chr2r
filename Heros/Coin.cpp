/**
 * Coin.cpp
 * Defines the Coin class.
 */

#include "Coin.h"
#include "SpriteSheet.h"
#include "GameScene.h"

#define ANIMATION_INTERVAL  (0.12)

Coin::Coin(Vector2 pos) :GameObject(false, pos, Vector2(12, 16)){
    spriteSheet_ = SpriteSheet::get("spr/terrain.bmp");
}

void Coin::update(GameScene *scene, double delta, Keys keys) {
    animationTime_ += delta;

    if (!pickedUp_ && animationTime_ >= ANIMATION_INTERVAL) {
        animationTime_ -= ANIMATION_INTERVAL;
        animationIndex_ = (animationIndex_ + 1) % 4;
    }
}

void Coin::entered_collision(GameScene *scene, GameObject *obj, Vector2 vec) {
    if (!pickedUp_ && obj == scene->player()){
        scene->sound_engine()->play2D("snd/smb_coin.wav");

        scene->add_score(1);
        pickedUp_ = true;
    }
}
void Coin::render(Viewport &vp) {
    if (pickedUp_) return;

    Texture t0 = { 219, 28, 12, 16 };
    Texture t1 = { 232, 28, 8, 16 };
    Texture t2 = { 241, 28, 6, 16 };
    Texture t3 = { 248, 28, 8, 16 };

    switch (animationIndex_) {
    case 0:
        spriteSheet_->draw(t0, position_, vp);
        break;
    case 1:
        spriteSheet_->draw(t1, position_, vp);
        break;
    case 2:
        spriteSheet_->draw(t2, position_, vp);
        break;
    case 3:
        spriteSheet_->draw(t3, position_, vp);
        break;
    }
}