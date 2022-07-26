#pragma once
#include "../AnimatedTexture2D.h"

enum class TurtleAnimation { SHORT = 0, LONG = 1};

class Turtle
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render(TurtleAnimation animationType = TurtleAnimation::SHORT);

private:
	
	//TurtleAnimation m_Animation;

	AnimatedTexture2D m_AnimatedTexture;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

