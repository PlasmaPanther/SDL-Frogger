#include "PlayState.h"
#include <iostream>

PlayState PlayState::s_Playstate;

bool PlayState::onEnter()
{

    std::cout << "Entering Playstate!" << std::endl;

    return true;
}

void PlayState::Update()
{

}

void PlayState::Render()
{

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
