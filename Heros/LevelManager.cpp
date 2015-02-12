#include "LevelManager.h"

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
    /* FIXME: delete contents of each layer */
}

void LevelManager::Add(GameObject * object, LevelManager::Layer layer)
{
	switch (layer)
	{
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