#pragma once
#include "../Texture2D.h"

class YellowCar
{
public:

	void Init(Vector2 _pos);

	void Update();
	void Render();

	void Clean();

private:

	Texture2D m_YellowCarTexture;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

