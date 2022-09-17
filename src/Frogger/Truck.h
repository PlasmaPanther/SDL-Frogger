#pragma once
#include "../AnimatedTexture2D.h"

class Truck
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();

	void Clean();

private:

	Texture2D m_TruckTexture;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

