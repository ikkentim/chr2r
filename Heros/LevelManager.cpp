#include "LevelManager.h"
#include <fstream>
#include "Block.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include "EnnemyFlying.h"
#include "EnnemyJumping.h"
#include "Coin.h"
#include "Player.h"
#include "Characters.h"
#include "Jumper.h"
#include <algorithm>
#include "LevelHeader.h"
#include "ObjectData.h"
#include "ActorData.h"
#include "JumpAbility.h"
#include "DuckAbility.h"
#include "SneakAbility.h"
#include "SplashAbility.h"
#include "SprintAbility.h"

using namespace std;

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
    for (auto o : playableLayer_)
        delete o;
    for (auto o : backgroundLayer_)
        delete o;
    for (auto o : foregroundLayer_)
        delete o;
}

LevelManager *LevelManager::load(const char * name, GameScene *scene, 
    Player *&player) {
    LevelManager *manager = new LevelManager();

    ifstream lvl;
    lvl.open(name, ios::in | ios::binary);

    LevelHeader header;
    lvl.read((char *)&header, sizeof(header));
    
    SpriteSheet *terrain = SpriteSheet::get(header.terrain_texture);

    ObjectData object_buffer;
    for (int i = 0; i < header.object_count; i++) {
        lvl.read((char *)&object_buffer, sizeof(object_buffer));

        GameObject *object = NULL;

        switch(object_buffer.type) {
        case BLOCK:
            object = new Block(terrain, object_buffer.texture,
                Vector2(object_buffer.x, object_buffer.y));
            break;
        case COIN:
            object = new Coin(Vector2(object_buffer.x, object_buffer.y));
            break;
		case JUMPER:
			object = new Jumper(Vector2(object_buffer.x, object_buffer.y));
			break;
        }

        manager->add(object, object_buffer.layer);
    }

    ActorData actor_buffer;
    for (int i = 0; i < header.actor_count; i++) {
        lvl.read((char *)&actor_buffer, sizeof(actor_buffer));

        Actor *actor = NULL;

        switch (actor_buffer.type) {
		case DOG:
			actor = new EnnemyDog(Vector2(actor_buffer.x, actor_buffer.y));
			break;
        case CHARACTER_MARIO:
            actor = new Mario(Vector2(actor_buffer.x, actor_buffer.y));
            break;
        case CHARACTER_SANIC:
            actor = new Sanic(Vector2(actor_buffer.x, actor_buffer.y));
            break;
        case CHARACTER_MAGIKARP:
            actor = new Magikarp(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case CHARACTER_SNAKE:
			actor = new Snake(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case FLYING_ENEMIE:
			actor = new EnnemyFlying(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case JUMPING_ENEMIE:
			actor = new EnnemyJumping(Vector2(actor_buffer.x, actor_buffer.y));
			break;
        }

        manager->add(actor, MOVABLE);
    }

    player = new Player(scene, Vector2(header.player_x, header.player_y));

    if (header.player_abilities & ABILITY_JUMP)
        player->give_ability(new JumpAbility);
    if (header.player_abilities & ABILITY_DUCK)
        player->give_ability(new DuckAbility);
    if (header.player_abilities & ABILITY_SNEAK)
        player->give_ability(new SneakAbility);
    if (header.player_abilities & ABILITY_SPLASH)
        player->give_ability(new SplashAbility);
    if (header.player_abilities & ABILITY_SPRINT)
        player->give_ability(new SprintAbility);

    manager->add(player, MOVABLE);

    manager->background_ = SpriteSheet::get(header.background_texture);
    manager->backgroundWidth_ = header.background_width;

    if (strlen(header.background_overlay_texture) > 0) {
        manager->backgroundOverlay_ = SpriteSheet::get(header.background_overlay_texture);
        manager->backgroundOverlayWidth_ = header.background_overlay_width;
    }

    strcpy_s(manager->nextLevel_, header.next_level);
    strcpy_s(manager->sound_, header.sound);

    manager->endGameX_ = header.end_game_x;
    manager->isEndGameRight_ = header.is_end_game_right;

    manager->bottomY_ = header.bottom;
    lvl.close();

    return manager;
}

void LevelManager::add(GameObject * object, LevelManager::Layer layer) {
	switch (layer) {
	case LevelManager::MOVABLE:
		movables()->push_back(object);
		playable_layer()->push_back(object);
		break;
	case LevelManager::BACKGROUND:
		background_layer()->push_back(object);
		break;
	case LevelManager::PLAYABLE:
		playable_layer()->push_back(object);
		break;
	case LevelManager::FOREGROUND:
		foreground_layer()->push_back(object);
		break;
	default:
		break;
	}
}