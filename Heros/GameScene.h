#pragma once
#include <irrKlang.h>
#include "DialogHUD.h"
#include "Scene.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameWindow.h"
#include <vector>
#include "Character.h"
#include "Ennemis.h"

class DialogHUD;
typedef std::vector <class HUD *> HUDVector;

class GameScene : public Scene {
public:
    GameScene(GameWindow *);
    virtual ~GameScene();
	virtual void Start();
    void Update(double, Keys);
    void Render(HDC graphics);
    irrklang::ISoundEngine *SoundEngine() {
        return window_->SoundEngine();
    }
    Player *player() {
        return player_;
    }
	
	LevelManager *level() {
        return level_;
    }
	bool paused;
	enum State {
		PLAYING,
		PLAYER_DEAD,
		REACHED_END,
		PAUSED,
		TALKING
	};
	virtual void SetState(State);
	virtual State GetState();
	DialogHUD *dialog_;
private:
	GameWindow *window_;
    Player *player_;
    HUDVector *hud_;
    LevelManager *level_;
    Viewport viewport_;
	
	void UpdateViewport();
	bool CheckStates();
	State state_;
	bool pausePressed_ = true;
};