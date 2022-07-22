#pragma once
#include "GameState.h"
#include "../Frogger/Frog.h"
#include <vector>
#include "../Shape2D.h"

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

	Frog m_Player;

	Texture2D m_PurpleSurface;
	Texture2D m_Grass;

	std::vector<Shape2D> m_lines;
};

