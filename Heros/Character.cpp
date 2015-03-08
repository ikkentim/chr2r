#include "Character.h"

Character::Character(Vector2 pos):Actor(pos, Vector2(16, 16)) {

}
void Character::Update(GameScene*, double delta, Keys) {
	Falling(delta);
}
void Character::Render(Viewport &vp) {
	Texture texture = {
		91, 0,
		16, 28
	};

	SpriteSheet::Get(SpriteSheet::MARIOCHAR)->Draw(texture, position_, vp);
}