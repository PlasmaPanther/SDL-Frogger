#pragma once
#include "../AnimatedTexture2D.h"

class Tractor
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();

	void Clean();

private:

	AnimatedTexture2D m_AnimatedTractorTexture;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

