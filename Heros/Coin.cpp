#include "Coin.h"
#include "SpriteSheet.h"

Coin::Coin(Texture tex) :texture_(tex), GameObject(){
}

Coin::Coin(Texture tex, Vector2 pos): texture_(tex), GameObject(pos, Vector2(tex.width, tex.height)){

}

void Coin::Update(GameScene *scene, double delta, Keys keys) {
	/* TODO: add the collision with character to delete it and +1 to total coin player */
}

void Coin::Render(Viewport &vp) {
	SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(texture_, position_, vp);
}