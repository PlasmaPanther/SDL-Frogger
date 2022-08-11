#pragma once
#include "Level.h"
#include "../Frog.h"
#include "../YellowCar.h"
#include "../Tractor.h"
#include "../PurpleCar.h"
#include "../WhiteCar.h"
#include "../Truck.h"
#include "../Turtle.h"
#include "../Log.h"
#include "../../Shape2D.h"
#include <vector>

class LevelOne: public Level
{
public:

	void Init();

	void Update();
	void Render();

	void Clean();

	static LevelOne* GetInstance();


private:

	void Place();

private:

	static LevelOne s_Instance;

	Frog m_Player;

	Texture2D m_BottomPurpleSurface;
	Texture2D m_TopPurpleSurface;

	Texture2D m_Grass;

	std::vector<Shape2D> m_lines;

	std::vector<YellowCar> m_YellowCarVector;
	std::vector<Tractor> m_TractorVector;
	std::vector<PurpleCar> m_PurpleCarVector;
	std::vector<WhiteCar> m_WhiteCarVector;
	std::vector<Truck> m_TruckVector;
	
	std::vector<Turtle> m_TurtleVector;
	std::vector<Log> m_LogVector;

	std::vector<Shape2D> m_Homes;

	Shape2D m_Lake;


};

