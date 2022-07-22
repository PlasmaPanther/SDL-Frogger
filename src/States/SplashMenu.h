#pragma once
#include "GameState.h"
#include "../Shape2D.h"
#include "../Font.h"
#include "../Frogger/FroggerEntrance.h"

class SplashMenu: public GameState
{
public:

	bool onEnter();

	void Update();
	void Render();

	bool onExit();

	static SplashMenu* GetInstance();

private:

	static SplashMenu s_SplashMenuInstance;

	Shape2D m_BlueSqare;

	Font m_OneUp;
	Font m_HiScore;
	Font m_OneUpValue;
	Font m_HiScoreValue;
	Font m_Credit;

	FroggerEntrance m_Entrance;
};

