#include "PlayState.h"
#include "../Frogger/Levels/LevelOne.h"
#include <iostream>

PlayState PlayState::s_Playstate;

bool PlayState::onEnter()
{

    std::cout << "Entering Playstate!" << std::endl;

    m_LevelManager.AddLevel(LevelOne::GetInstance());

    return true;
}

void PlayState::Update()
{
    m_LevelManager.Update();
}

void PlayState::Render()
{
    m_LevelManager.Render();
}

bool PlayState::onExit()
{

    std::cout << "Exiting Playstate!" << std::endl;

    return true;
}

PlayState* PlayState::GetInstance()
{
    return &s_Playstate;
}
