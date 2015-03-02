#include "Coin.h"
#include "SpriteSheet.h"
#include "GameScene.h"

#define ANIMATION_INTERVAL  (0.12)

Coin::Coin(Vector2 pos) :GameObject(false, pos, Vector2(12, 16)){

}

void Coin::Update(GameScene *scene, double delta, Keys keys) {
    animationTime_ += delta;

    if (!pickedUp_ && animationTime_ >= ANIMATION_INTERVAL) {
        animationTime_ -= ANIMATION_INTERVAL;
        animationIndex_ = (animationIndex_ + 1) % 4;
    }
}

void Coin::EnteredCollision(GameScene *scene, GameObject *obj, Vector2 vec) {
    if (!pickedUp_ && obj == scene->player()){
        scene->SoundEngine()->play2D("snd/smb_coin.wav");

        pickedUp_ = true;
    }
}
void Coin::Render(Viewport &vp) {
    if (pickedUp_) return;

    Texture t0 = { 219, 28, 12, 16 };
    Texture t1 = { 232, 28, 8, 16 };
    Texture t2 = { 241, 28, 6, 16 };
    Texture t3 = { 248, 28, 8, 16 };

    switch (animationIndex_) {
    case 0:
        SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(t0, position_, vp);
        break;
    case 1:
        SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(t1, position_, vp);
        break;
    case 2:
        SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(t2, position_, vp);
        break;
    case 3:
        SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(t3, position_, vp);
        break;
    }
}