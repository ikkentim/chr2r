#include "GameScene.h"
#include "Block.h"
#include "Coin.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include <irrKlang.h>
#include "DialogHUD.h"

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    
    hud_ = new HUDVector;
	level_ = LevelManager::Load("lvl/level01.dat", this, player_);

    hud_->push_back(new TestHUD);
}

GameScene::~GameScene() {
    delete level_;
    delete player_; /* FIXME: Should be deleted by level_ */
}
void GameScene::Start() {
    /* Testing sound */
	SoundEngine()->play2D("snd/01-main-theme-overworld.mp3", true);
}
void GameScene::Update(double delta, Keys keys) {

    /* Update viewport */

    /* Minimum distance between window edge and the player*/
    const int borderOffset = 215; 
    

    int minx = viewport_.x + borderOffset;
    int maxx = viewport_.x - borderOffset + viewport_.width;

    int miny = viewport_.y + borderOffset;
    int maxy = viewport_.y - borderOffset + viewport_.height;

    auto pos = player_->Position();
    int posx = (int)floor(pos.x);
    int posy = (int)floor(pos.y);

    if (posx < minx) viewport_.x += posx - minx;
    else if (posx > maxx) viewport_.x += posx - maxx;

    if (posy < miny) viewport_.y += posy - miny;
    else if (posy > maxy) viewport_.y += posy - maxy;

	if (player()->GetState() == Actor::DEAD)
	{
		window_->UpdateScene(new GameScene(window_));
		return;
	}

    /* playablelayer */
    LevelLayer *layer = level_->PlayableLayer();
    for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
        GameObject *object = *iter;

        object->Update(this, delta, keys);
    }
    /* Check collision on movableslayer */    
    layer = level_->Movables();
    for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
        GameObject *object = *iter;
        object->CheckForCollisions(this, level_->PlayableLayer(), delta);
        object->ApplyVelocity(delta);
    }
	}
    /* Update HUD */
    for (HUDVector::iterator it = hud_->begin(); it != hud_->end(); ++it) {
        HUD *hud = *it;
        hud->Update(this, delta, keys);
    }
}

void GameScene::Render(double delta, HDC graphics) {

    /* Draw background */
    /* FIXME: Make LevelManager decide background */
    /* FIXME: backgrounds can have different widths */
    const int image_width = 727;
    Texture tex = { 0, 0, image_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        SpriteSheet::Get(SpriteSheet::BACKGROUND01)->Draw(tex, skyx, 0);
	}

	/* Render all layers */
	LevelLayer *layer;

	layer = level_->BackgroundLayer();
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}
	layer = level_->PlayableLayer();
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}
	layer = level_->ForegroundLayer();
	for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
		GameObject *object = *it;
		object->Render(viewport_);
	}

    /* Render HUD */
    for (HUDVector::iterator it = hud_->begin(); it != hud_->end(); ++it) {
        HUD *hud = *it;
        hud->Render(graphics);
    }
}