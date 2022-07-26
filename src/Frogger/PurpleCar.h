#pragma once
#include "../Texture2D.h"

class PurpleCar
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();

private:

	Texture2D m_Texture2D;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

