#include "LevelOne.h"

LevelOne LevelOne::s_Instance;

void LevelOne::Init()
{

    m_Player.Init(Vector2(370, 530));

    m_BottomPurpleSurface.LoadClippedTexture("frogger_sprites.png", 0, 118, Vector2(0, 526), 800, 34, Vector2(1.0f, 1.0f));
    m_TopPurpleSurface.LoadClippedTexture("frogger_sprites.png", 0, 118, Vector2(0, 295), 800, 34, VEC2_ONE);

    m_Grass.LoadClippedTexture("frogger_sprites.png", 0, 54, Vector2(0, 50), 800, 51, VEC2_ONE);

    m_lines.resize(13);

    m_YellowCarVector.resize(4);

    Vector2 YellowCarOffset = { 250, 493 };

    for (int i = 0; i < m_YellowCarVector.size(); ++i) {
        m_YellowCarVector[i].Init(YellowCarOffset);

        YellowCarOffset.x += 220;
    }

    m_TractorVector.resize(3);

    Vector2 TractorOffset = { 200, 453 };

    for (int i = 0; i < m_TractorVector.size(); ++i) {

        m_TractorVector[i].Init(TractorOffset);

        TractorOffset.x += 300;

    }

    m_PurpleCarVector.resize(3);

    Vector2 PurpleCarOffset = { 200, 415 };

    for (int i = 0; i < m_PurpleCarVector.size(); ++i) {
        m_PurpleCarVector[i].Init(PurpleCarOffset);

        PurpleCarOffset.x += 250;
    }

    m_WhiteCarVector.resize(1);

    m_WhiteCarVector.back().Init(Vector2(300, 374));

    m_TruckVector.resize(2);

    Vector2 TruckOffset = { 150, 325 };

    for (int i = 0; i < m_TruckVector.size(); ++i) {
        m_TruckVector[i].Init(TruckOffset);

        TruckOffset.x += 450;
    }

    m_TurtleVector.resize(20);

    Vector2 BottomTurtleOffset = { 50, 259 };
    Vector2 TopTurtleOffset = { 50, 140 };

    for (int i = 0; i < m_TurtleVector.size(); ++i) {

        m_TurtleVector[i].Init(BottomTurtleOffset);

        BottomTurtleOffset.x += 50;

        if (i == 2 || i == 5 || i == 8) {
            BottomTurtleOffset.x += 50;
        }

        if (i > 11) {

            m_TurtleVector[i].Init(TopTurtleOffset);
            TopTurtleOffset.x += 50;

            if (i == 13 || i == 15 || i == 17 || i == 19) {
                TopTurtleOffset.x += 80;
            }

        }

    }

    m_LogVector.resize(9);

    Vector2 ShortLogOffset = { 2, 218 };
    Vector2 MediumLogOffset = { 5, 180 };
    Vector2 LongLogOffset = { 1, 103 };

    for (int i = 0; i < m_LogVector.size(); ++i) {
        
        if (i < 3) {
            m_LogVector[i].Init(ShortLogOffset, LogType::SHORT);
            ShortLogOffset.x += 230;
        }

        if (i >= 3 && i <= 5) {
            m_LogVector[i].Init(LongLogOffset, LogType::LONG);
            LongLogOffset.x += 350;
        }

        if (i >= 6) {
            m_LogVector[i].Init(MediumLogOffset, LogType::MEDIUM);
            MediumLogOffset.x += 260;
        }

    }

}

void LevelOne::Update()
{
    m_Player.Update();

    for (int i = 0; i < m_YellowCarVector.size(); ++i) {
        m_YellowCarVector[i].Update();
    }

    for (int i = 0; i < m_TractorVector.size(); ++i) {
        m_TractorVector[i].Update();
    }

    for (int i = 0; i < m_PurpleCarVector.size(); ++i) {
        m_PurpleCarVector[i].Update();
    }

    m_WhiteCarVector.back().Update();

    for (int i = 0; i < m_TruckVector.size(); ++i) {
        m_TruckVector[i].Update();
    }

    for (int i = 0; i < m_TurtleVector.size(); ++i) {
        m_TurtleVector[i].Update();
    }

    for (int i = 0; i < m_LogVector.size(); ++i) {
        m_LogVector[i].Update();
    }

}

void LevelOne::Render()
{

    Vector2 offset(0, 60);

    for (int i = 0; i < m_lines.size(); ++i) {
        m_lines[i].PlaceLine(0, offset.y, 800, offset.y);
        offset.y += 39;
    }

    for (int i = 0; i < m_YellowCarVector.size(); ++i) {
        m_YellowCarVector[i].Render();
    }

    for (int i = 0; i < m_TractorVector.size(); ++i) {
        m_TractorVector[i].Render();
    }

    for (int i = 0; i < m_PurpleCarVector.size(); ++i) {
        m_PurpleCarVector[i].Render();
    }

    m_WhiteCarVector.back().Render();

    for (int i = 0; i < m_TruckVector.size(); ++i) {
        m_TruckVector[i].Render();
    }

    for (int i = 0; i < m_TurtleVector.size(); ++i) {

        if (i > 5 && i < 9) {
            m_TurtleVector[i].Render(TurtleAnimation::LONG);
        }
        else {
            m_TurtleVector[i].Render();
        }

    }

    for (int i = 0; i < m_LogVector.size(); ++i) {
        m_LogVector[i].Render();
    }

    m_Grass.RenderClippedTexture();

    m_BottomPurpleSurface.RenderClippedTexture();
    m_TopPurpleSurface.RenderClippedTexture();

    m_Player.Render();

}

void LevelOne::Clean()
{
    
}

LevelOne* LevelOne::GetInstance()
{
    return &s_Instance;
}
