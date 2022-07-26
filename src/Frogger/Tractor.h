#pragma once
#include "../AnimatedTexture2D.h"

class Tractor
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();


private:

	AnimatedTexture2D m_AnimatedTexture;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

