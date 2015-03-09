#include "Character.h"

Character::Character(Vector2 pos):Actor(pos, Vector2(16, 16)) {
    spriteSheet_ = SpriteSheet::Get("spr/mario.bmp");
}
void Character::Update(GameScene*, double delta, Keys) {
	Falling(delta);
}
void Character::Render(Viewport &vp) {
	Texture texture = {
		91, 0,
		16, 28
	};

    spriteSheet_->Draw(texture, position_, vp);
}