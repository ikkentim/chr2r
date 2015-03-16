#include "GameScene.h"
#include "Block.h"
#include "Coin.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include <irrKlang.h>
#include "DialogHUD.h"
#include "TestHUD.h"
#include "MenuScene.h"
#include <algorithm>
#include "EndGameScene.h"

GameScene::GameScene(GameWindow *window)
	:window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    
    hud_ = new HUDVector;
	level_ = LevelManager::Load("lvl/level01.dat", this, player_);

	state_ = PLAYING;
	
	hud_->push_back(new DialogHUD(player_, this));
	hud_->push_back(new TestHUD());

	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;

	LevelLayer *layer = level_->PlayableLayer();
	for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
		GameObject *object = *iter;

		minX = min(minX, object->Position().x);
		maxX = max(maxX, object->Position().x);
		minY = min(minY, object->Position().y);
		maxY = max(maxY, object->Position().y);
	}

	int boxX = (minX + maxX) / 2;
	int boxY = (minY + maxY) / 2;

	quadTree_ = new QuadTree(new AABB(Vector2(boxX, boxY), Vector2(maxX - minX + 100, maxY - minY + 100)));

	/* playablelayer */
	layer = level_->PlayableLayer();
	for (LevelLayer::iterator iter = layer->begin(); iter != layer->end(); ++iter) {
		GameObject *object = *iter;

		if (object == NULL || object == player())
			continue;

		quadTree_->Insert(object);
	}
}

GameScene::~GameScene() {
    delete level_;
	delete quadTree_;
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
	case PAUSED:
		return;
	case TALKING:
		return;
	case PLAYER_DEAD:
		if (player()->Die())
		{
			
			window_->UpdateScene(new MenuScene(window_));
			return;
		}
		player()->SetState(Player::ALIVE);
		state_ = PLAYING;
		return;
    case REACHED_END:
        
        if (level_->isLastLevel()) {
            window_->UpdateScene(new EndGameScene(window_));
        }
        else {
            delete level_;
            level_ = LevelManager::Load(level_->nextLevel(), this, player_);
            SetState(PLAYING);
        }
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

		AABB* queryBox = new AABB(object->Position(), Vector2(32, 32));

		int count = quadTree_->QueryRange(queryBox, collisionBuffer_, 0);

		delete queryBox;

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
    const int borderOffsetTop = 340;
    const int borderOffsetBottom = 100;

	int minx = viewport_.x + borderOffset;
	int maxx = viewport_.x - borderOffset + viewport_.width;

    int miny = viewport_.y + borderOffsetTop;
    int maxy = viewport_.y - borderOffsetBottom + viewport_.height;

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
    const int image2_width = level_->backgroundOverlayWidth();
    Texture tex = { 0, 0, image_width, viewport_.height };
    Texture tex2 = { 0, 0, image2_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        level_->background()->Draw(tex, skyx, 0);
	}
    if (level_->backgroundOverlay())
        for (int skyx = -(viewport_.x / 3) % image2_width - image2_width;
            skyx <= viewport_.width; skyx += image2_width) {
        level_->backgroundOverlay()->Draw(tex2, skyx, 0);
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