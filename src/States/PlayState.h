#pragma once
#include "GameState.h"

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

};

