#include "SplashMenu.h"
#include "PlayState.h"
#include "StateMachine.h"
#include "../Input.h"
#include <iostream>

SplashMenu SplashMenu::s_SplashMenuInstance;

bool SplashMenu::onEnter()
{
	std::cout << "Entering Splash Menu!" << std::endl;

	m_BlueSqare.PlaceRect(Vector2(0, 0), 800, 300);

	m_OneUp.Load("Emulogic.ttf", 24, "1-UP", Colors::WHITE);
	m_OneUpValue.Load("Emulogic.ttf", 24, "01580", Colors::RED);

	m_HiScore.Load("Emulogic.ttf", 24, "HI-SCORE", Colors::WHITE);
	m_HiScoreValue.Load("Emulogic.ttf", 24, "04630", Colors::RED);

	m_Credit.Load("Emulogic.ttf", 24, "Credit 00", Colors::CYAN);

	m_Entrance.Init(Vector2(850, 320));

	return true;
}

void SplashMenu::Update()
{
	if (Input::KeyPressed(SDL_SCANCODE_C)) {
		std::cout << "Key Pressed" << std::endl;
	}

	m_Entrance.Update();

	if (m_Entrance.IsAnimationDone()) {
		
	}

}

void SplashMenu::Render()
{
	m_BlueSqare.DrawRect(0, 0, 80, 255);

	m_OneUp.Render(Vector2(90, 0));
	m_OneUpValue.Render(Vector2(90, 24));

	m_HiScore.Render(Vector2(320, 0));
	m_HiScoreValue.Render(Vector2(320, 24));

	m_Credit.Render(Vector2(550, 565));

	m_Entrance.Render();

}

bool SplashMenu::onExit()
{

	std::cout << "Exiting Splash Menu!" << std::endl;

	m_Entrance.Clean();

	m_OneUp.FreeFont();
	m_OneUpValue.FreeFont();

	m_HiScore.FreeFont();
	m_HiScoreValue.FreeFont();

	m_Credit.FreeFont();

	return true;
}

SplashMenu* SplashMenu::GetInstance()
{
	return &s_SplashMenuInstance;
}
