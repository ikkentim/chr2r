#include "Character.h"

Character::Character(Vector2 pos):Actor(pos, Vector2(16, 16)) {

}
void Character::Update(GameScene*, double, Keys) {

}
void Character::Render(Viewport &vp) {
	Texture texture = {
		257, 247,
		16, 16
	};

	SpriteSheet::Get(SpriteSheet::TERRAIN)->Draw(texture, position_, vp);
}