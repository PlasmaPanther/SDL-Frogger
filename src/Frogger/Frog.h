#pragma once
#include "../AnimatedTexture2D.h"

enum class Directions { NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4};

class Frog
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();

	//These functions will help with rendering the frogs at the splash menu
	void EntranceRender(bool inHorizontalPos = false, bool AllInPosition = false, bool renderFlag = true);
	void Move(Vector2 _vel) { m_Texture2D.Move(_vel); m_AnimatedTexture.Move(_vel); m_Position += _vel; }
	Vector2 GetPosition() { return m_Position; }
	//======================================================================

private:

	Directions m_FrogDirections;

	AnimatedTexture2D m_AnimatedTexture;
	Texture2D m_Texture2D;

	Vector2 circlepos;
	Vector2 m_Velocity;
	Vector2 m_Position;
};

