#include "GameScene.h"
#include "Block.h"
#include "Coin.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include <irrKlang.h>
#include "DialogHUD.h"
#include "TestHUD.h"
#include "MenuScene.h"

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    
    hud_ = new HUDVector;
	level_ = LevelManager::Load("lvl/level01.dat", this, player_);

	state_ = PLAYING;
	
	hud_->push_back(new DialogHUD(player_, this));
	hud_->push_back(new TestHUD());

	quadTree_ = new QuadTree(new AABB(Vector2(10000, 10000), Vector2(10000, 10000)));

	/* playablelayer */
	LevelLayer *layer = level_->PlayableLayer();
	for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
		GameObject *object = *iter;

		if (object == NULL)
			continue;

		quadTree_->Insert(object);
	}
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
	UpdateViewport();

	CheckStates();

	///* Update HUD */
	//for (HUDVector::iterator it = hud_->begin(); it != hud_->end(); ++it) {
	//	HUD *hud = *it;
	//	hud->Update(this, delta, keys);
	//}

	switch (state_)
	{
	case State::PAUSED:
		return;
	case State::TALKING:
		return;
	case State::PLAYER_DEAD:
		if (player()->Die())
		{
			window_->UpdateScene(new MenuScene(window_));
			return;
		}
		player()->SetState(Player::ALIVE);
		state_ = PLAYING;
		return;
	default:
		break;
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

		int count = quadTree_->QueryRange(AABB(object->Position(), Vector2(32, 32)), collisionBuffer_, 0);

		object->CheckForCollisions(this, collisionBuffer_, count, delta);

		quadTree_->Delete(object);
        object->ApplyVelocity(delta);
		quadTree_->Insert(object);
    }
}

void GameScene::UpdateViewport()
{
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
}

bool GameScene::CheckStates()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		if (!pausePressed_)
		{
			if (GetState() == PLAYING)
				SetState(PAUSED);
			else
				SetState(PLAYING);

			pausePressed_ = true;
		}
	}
	else
	{
		pausePressed_ = false;
	}

	if (level_->bottomY() < player()->Position().y)
	{
		player()->SetState(Actor::DEAD);
		SetState(PLAYER_DEAD);
	}

	if (player()->GetState() == Actor::DEAD)
	{
		SetState(PLAYER_DEAD);
		return true;
	}

	return false;
}

void GameScene::Render(HDC graphics) {

    /* Draw background */
    const int image_width = level_->backgroundWidth();
    Texture tex = { 0, 0, image_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        level_->background()->Draw(tex, skyx, 0);
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

void GameScene::SetState(State state)
{
	state_ = state;
}

GameScene::State GameScene::GetState()
{
	return state_;
}