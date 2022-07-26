#pragma once
#include "../AnimatedTexture2D.h"

class Truck
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

