#include "PlayState.h"
#include <iostream>

PlayState PlayState::s_Playstate;

bool PlayState::onEnter()
{

    std::cout << "Entering Playstate!" << std::endl;

    m_Player.Init(Vector2(320, 521));

    m_PurpleSurface.LoadClippedTexture("frogger_spritesF.png", 0, 118, Vector2(0, 520), 800, 34, 1.0f);
    m_Grass.LoadClippedTexture("frogger_spritesF.png", 0, 54, Vector2(0, 50), 800, 51, 1.0f);

    m_lines.resize(13);

    return true;
}

void PlayState::Update()
{
    m_Player.Update();
}

void PlayState::Render()
{

   Vector2 offset(0, 60);

    for (int i = 0; i < m_lines.size(); ++i) {
        m_lines[i].PlaceLine(0, offset.y, 800, offset.y);
        offset.y += 39;
    }

    m_Grass.RenderClippedTexture();

    m_PurpleSurface.RenderClippedTexture();

    m_Player.Render();
}

bool PlayState::onExit()
{

    std::cout << "Exiting Playstate!" << std::endl;

    m_Player.Clean();

    return true;
}

PlayState* PlayState::GetInstance()
{
    return &s_Playstate;
}
