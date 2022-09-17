#include <fstream>
#include <iostream>

#include "LevelOne.h"
#include "../../CollisionManager.h"
#include "../../Input.h"

LevelOne LevelOne::s_Instance;

void LevelOne::Init()
{

    this->Place(); //Initializes positions of entities

    int HiScore;

    std::ifstream Input;
    Input.open("src/Frogger/Score.txt");

    if (!Input.is_open() || !Input.good()) {
        std::cout << "Cannot read from file" << std::endl;
    }

    Input >> HiScore;

    Input.close();

    m_OneUpText.Load("Emulogic.ttf", 22, "1-UP", Colors::RED);
    m_OneUPScore.LoadToText("Emulogic.ttf", 22, 0, Colors::WHITE);

    m_HI_ScoreText.Load("Emulogic.ttf", 22, "HI-SCORE", Colors::RED);
    m_HiScore.LoadToText("Emulogic.ttf", 22, HiScore, Colors::WHITE);

    m_TimeText.Load("Emulogic.ttf", 20, "TIME", Colors::YELLOW);

    //These will not be able to collide with each other
    CollisionManager::IgnoreCollider("enviorment");
    CollisionManager::IgnoreCollider("short_logs");
    CollisionManager::IgnoreCollider("medium_logs");
    CollisionManager::IgnoreCollider("long_logs");
    CollisionManager::IgnoreCollider("turtles");
    //===============================================

    m_BottomPurpleSurface.LoadClippedTexture("frogger_sprites.png", 0, 118, Vector2(0, 526), 800, 34, Vector2(1.0f, 1.0f));
    m_TopPurpleSurface.LoadClippedTexture("frogger_sprites.png", 0, 118, Vector2(0, 295), 800, 34, VEC2_ONE);

    m_Grass.LoadClippedTexture("frogger_sprites.png", 0, 54, Vector2(0, 50), 800, 51, VEC2_ONE);

    m_Music.PlayMusic("Frogger_Theme.wav", 0);

    m_Music.SetMusicVolume(50);

    m_StageMusic = false;
    m_ThemeMusic = true;

}

void LevelOne::Update()
{
    //there is a function in sdl_mixer that checks when a song ends but that doesn't seem to work properly
    //so i need to use this scuffed solution
    if (m_Music.GetMusicTime() >= 7 && m_ThemeMusic) {

        m_StageMusic = true;
        m_ThemeMusic = false;

    }

    if (m_StageMusic) {
        m_Music.PlayMusic("Frogger_Stage.wav", -1);

        m_StageMusic = false;
    }

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
    
    if (!m_WhiteCarVector.empty()) {
        m_WhiteCarVector.back().Update();
    }
    for (int i = 0; i < m_TruckVector.size(); ++i) {
        m_TruckVector[i].Update();
    }

    for (int i = 0; i < m_TurtleVector.size(); ++i) {
        m_TurtleVector[i].Update();
    }

    for (int i = 0; i < m_LogVector.size(); ++i) {
        m_LogVector[i].Update();
    }

    m_OneUPScore.ChangeToText(m_Player.GetScore(), Colors::WHITE);
}

void LevelOne::Render()
{
    m_Lake.RenderRect(0, 0, 70, 255);

    m_OneUpText.Render(Vector2(150, 0));
    m_OneUPScore.Render(Vector2(155, 25));

    m_HI_ScoreText.Render(Vector2(320, 0));
    m_HiScore.Render(Vector2(320, 25));

    m_TimeText.Render(Vector2(700, 575));

    Vector2 offset(0, 60);

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

void LevelOne::Place()
{

    m_Player.Init(Vector2(370, 530));

    m_Homes.resize(5);

    for (int i = 0; i < m_Homes.size(); ++i) {

        m_Homes[i].Place(Vector2(25 + (i * 170), 70), Vector2(60, 30));

        CollisionManager::AddCollider(&m_Homes[i], "home" + std::to_string(i));
        CollisionManager::IgnoreCollider("home" + std::to_string(i)); //to avoid "colliding" with the lake
    }

    m_Lake.Place(Vector2(0, 0), Vector2(800, 300));

    CollisionManager::AddCollider(&m_Lake, "enviorment");

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

    Vector2 TruckOffset = { 150, 335 };

    for (int i = 0; i < m_TruckVector.size(); ++i) {
        m_TruckVector[i].Init(TruckOffset);

        TruckOffset.x += 400;
    }

    m_TurtleVector.resize(20);

    Vector2 BottomTurtleOffset = { 50, 259 };
    Vector2 TopTurtleOffset = { 50, 140 };

    for (int i = 0; i < m_TurtleVector.size(); ++i) {

        if (i <= 11) {

            m_TurtleVector[i].Init(BottomTurtleOffset);

            BottomTurtleOffset.x += 50;

            if (i == 2 || i == 5 || i == 8) {
                BottomTurtleOffset.x += 80;
            }

        }

        if (i >= 12) {

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
            ShortLogOffset.x += 300;
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


void LevelOne::Clean()
{
    m_Player.Clean();
    
    for (auto& Logs : m_LogVector) {
        Logs.Clean();
    }

    m_LogVector.clear();

    for (auto& PurpleCar : m_PurpleCarVector) {
        PurpleCar.Clean();
    }

    m_PurpleCarVector.clear();

    for (auto& Tractor : m_TractorVector) {
        Tractor.Clean();
    }

    m_TractorVector.clear();

    for (auto& Truck : m_TruckVector) {
        Truck.Clean();
    }

    m_TruckVector.clear();

    for (auto& Turtles : m_TurtleVector) {
        Turtles.Clean();
    }

    m_TurtleVector.clear();

    for (auto& WhiteCars : m_WhiteCarVector) {
        WhiteCars.Clean();
    }

    m_WhiteCarVector.clear();

    for (auto& YellowCars : m_YellowCarVector) {
        YellowCars.Clean();
    }

    m_YellowCarVector.clear();

    m_OneUpText.FreeFont();
    m_OneUPScore.FreeFont();

    m_HI_ScoreText.FreeFont();
    m_HiScore.FreeFont();

    m_TimeText.FreeFont();
}

LevelOne* LevelOne::GetInstance()
{
    return &s_Instance;
}