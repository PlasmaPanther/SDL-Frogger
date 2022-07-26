#pragma once
#include "GameState.h"
#include "../Frogger/Levels/LevelManager.h"

class PlayState: public GameState 
{
public:

	bool onEnter();

	void Update();
	void Render();

	bool onExit();

	static PlayState* GetInstance();

private:

	static PlayState s_Playstate;

	LevelManager m_LevelManager;
};

