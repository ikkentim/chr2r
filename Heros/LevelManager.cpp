#include "LevelManager.h"
#include <fstream>
#include "Block.h"
#include "Ennemis.h"
#include "EnnemyDog.h"
#include "EnnemyFlying.h"
#include "EnnemyJumping.h"
#include "Coin.h"
#include "Player.h"
#include "Character.h"
#include <algorithm>

#include "LevelHeader.h"
#include "ObjectData.h"

enum ActorType {
	//ENNEMIS,
	DOG,
	FLYING_ENEMIE,
	JUMPING_ENEMIE,
	CHARACTER
};

struct ActorData {
    int x;
    int y;
    ActorType type;
};
using namespace std;

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
}

LevelManager *LevelManager::Load(const char * name, GameScene *scene, 
    Player *&player) {
    LevelManager *manager = new LevelManager();

    ifstream lvl;
    lvl.open(name, ios::in | ios::binary);

    LevelHeader header;
    lvl.read((char *)&header, sizeof(header));
    
    SpriteSheet *terrain = SpriteSheet::Get(header.terrain_texture);

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
        }

        manager->Add(object, object_buffer.layer);
    }

    ActorData actor_buffer;
    for (int i = 0; i < header.actor_count; i++) {
        lvl.read((char *)&actor_buffer, sizeof(actor_buffer));

        Actor *actor = NULL;

        switch (actor_buffer.type) {
        //case ENNEMIS:
        //    actor = new Ennemis(Vector2(actor_buffer.x, actor_buffer.y));
        //    break;
		case DOG:
			actor = new EnnemyDog(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case CHARACTER:
			actor = new Character(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case FLYING_ENEMIE:
			actor = new EnnemyFlying(Vector2(actor_buffer.x, actor_buffer.y));
			break;
		case JUMPING_ENEMIE:
			actor = new EnnemyJumping(Vector2(actor_buffer.x, actor_buffer.y));
			break;
        }

        manager->Add(actor, MOVABLE);
    }

    player = new Player(scene, Vector2(header.player_x, header.player_y));
    manager->Add(player, MOVABLE);

    manager->background_ = SpriteSheet::Get(header.background_texture);
    manager->backgroundWidth_ = header.background_width;

    manager->bottomY_ = header.bottom;
    lvl.close();

    return manager;
}


/* TEMPORARY FUNCTION! */
void LevelManager::WriteSimpleLevel()
{
    LevelHeader lvl;
    lvl.bottom = 500;
    lvl.player_x = 16;
    lvl.player_y = 240;
    lvl.player_abilities_ph = 0;
    sprintf_s(lvl.name, "Level 01!");
    sprintf_s(lvl.background_texture, "spr/background01.bmp");
    lvl.background_width = 727;
    sprintf_s(lvl.terrain_texture, "spr/terrain.bmp");
    lvl.object_count = 2160 + 16;
    lvl.actor_count = 4;

    ofstream lvlout;
    lvlout.open("level01.dat", ios::out | ios::binary);

    lvlout.write((char *)&lvl, sizeof(lvl));

    Texture grass_top = { 444, 253, 16, 16 };
    Texture grass_middle = { 444, 270, 16, 16 };

    Texture grass_tl = { 427, 202, 16, 16 };
    Texture grass_tr = { 461, 202, 16, 16 };

    Texture grass_left = { 427, 219, 16, 16 };
    Texture grass_right = { 461, 219, 16, 16 };

    Texture air_block = { 257, 97, 16, 16 };
    Texture question = { 208, 181, 16, 16 };

    Texture pipe_tl = { 1, 179, 16, 15 };
    Texture pipe_tr = { 19, 179, 16, 15 };
    Texture pipe_bl = { 1, 195, 16, 16 };
    Texture pipe_br = { 19, 195, 16, 16 };

    ObjectData obj;
    obj.width = 16;
    obj.height = 16;
    obj.texture = grass_tl;
    obj.type = BLOCK;
    obj.layer = PLAYABLE;

    for (int x = -10; x < 25; x++)
        for (int y = 0; y < 20; y++) {
            obj.x = 16 * x;
            obj.y = 16 * y + 256;

            obj.layer = PLAYABLE;

            if (x == -10 && y == 0)
                obj.texture = grass_tl;
            else if (x == 24 && y == 0)
                obj.texture = grass_tr;
            else if (y == 0)
                obj.texture = grass_top;
            else if (x == -10) {
                obj.layer = FOREGROUND;
                obj.texture = grass_left;
            }
            else if (x == 24) {
                obj.layer = FOREGROUND;
                obj.texture = grass_right;
            }
            else {
                obj.layer = FOREGROUND;
                obj.texture = grass_middle;
            }

            lvlout.write((char *)&obj, sizeof(ObjectData));
        }

    for (int x = 28; x < 100; x++)
        for (int y = 0; y < 20; y++) {
            obj.x = 16 * x;
            obj.y = 16 * y + 256;

            obj.layer = PLAYABLE;

            if (x == 28 && y == 0)
                obj.texture = grass_tl;
            else if (x == 99 && y == 0)
                obj.texture = grass_tr;
            else if (y == 0)
                obj.texture = grass_top;
            else if (x == 28) {
                obj.layer = FOREGROUND;
                obj.texture = grass_left;
            }
            else if (x == 99) {
                obj.layer = FOREGROUND;
                obj.texture = grass_right;
            }
            else {
                obj.layer = FOREGROUND;
                obj.texture = grass_middle;
            }

            lvlout.write((char *)&obj, sizeof(ObjectData));
        }

    obj.layer = PLAYABLE;

    for (int x = 0; x < 3; x++) {
        obj.x = 96 + (16 * x);
        obj.y = 192;
        obj.texture = air_block;

        lvlout.write((char *)&obj, sizeof(ObjectData));
    }

    for (int x = 0; x < 4; x++) {
        obj.x = 480 + (16 * x);
        obj.y = 192;
        obj.texture = air_block;

        lvlout.write((char *)&obj, sizeof(ObjectData));
    }

    for (int x = 0; x < 8; x++) {
        obj.x = 544 + (16 * x);
        obj.y = 128;
        obj.texture = air_block;

        lvlout.write((char *)&obj, sizeof(ObjectData));
    }

    obj.x = 112;
    obj.y = 192;
    obj.texture = question;
    lvlout.write((char *)&obj, sizeof(ObjectData));

    obj.x = 256;
    obj.y = 224;
    obj.height = 15;
    obj.texture = pipe_tl;
    lvlout.write((char *)&obj, sizeof(ObjectData));

    obj.x = 272;
    obj.y = 224;
    obj.height = 15;
    obj.texture = pipe_tr;
    lvlout.write((char *)&obj, sizeof(ObjectData));

    obj.x = 256;
    obj.y = 240;
    obj.height = 16;
    obj.texture = pipe_bl;
    lvlout.write((char *)&obj, sizeof(ObjectData));

    obj.x = 272;
    obj.y = 240;
    obj.height = 16;
    obj.texture = pipe_br;
    lvlout.write((char *)&obj, sizeof(ObjectData));


    for (int x = 0; x < 16; x++) {
        obj.x = 96 + (32 * x);
        obj.y = 175;
        obj.texture = { 0, 0, 0, 0 };
        obj.type = COIN;

        lvlout.write((char *)&obj, sizeof(ObjectData));
    }

    ActorData actor;



    //actor.x = 80;
    //actor.y = 240;
    //actor.type = ENNEMIS;
    //lvlout.write((char *)&actor, sizeof(ActorData));

    actor.x = 1000;
    actor.y = 240;
    actor.type = DOG;
    lvlout.write((char *)&actor, sizeof(ActorData));

	actor.x = 100;
	actor.y = 300;
	actor.type = FLYING_ENEMIE;
	lvlout.write((char*)&actor, sizeof(ActorData));

	actor.x = 250;
	actor.y = 240;
	actor.type = JUMPING_ENEMIE;
	lvlout.write((char *)&actor, sizeof(ActorData));
		
	//lvlout.write((char *)&actor, sizeof(ActorData));

	actor.x = 200;
	actor.y = 100;
	actor.type = CHARACTER;
	lvlout.write((char *)&actor, sizeof(ActorData));


    lvlout.close();
}

void LevelManager::Add(GameObject * object, LevelManager::Layer layer) {
	switch (layer) {
	case LevelManager::MOVABLE:
		Movables()->push_back(object);
		PlayableLayer()->push_back(object);
		break;
	case LevelManager::BACKGROUND:
		BackgroundLayer()->push_back(object);
		break;
	case LevelManager::PLAYABLE:
		PlayableLayer()->push_back(object);
		break;
	case LevelManager::FOREGROUND:
		ForegroundLayer()->push_back(object);
		break;
	default:
		break;
	}
}