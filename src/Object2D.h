#pragma once
#include "Graphics.h"
#include "Math.h"

class Object2D
{
public:
	Object2D(float x = 0.0f, float y = 0.0f);
	~Object2D() = default;

	void Move(Vector2 _vec);

	friend bool CheckCollision(Object2D& ObjectA, Object2D& ObjectB);
	
	SDL_FRect& GetRect();

protected:

	SDL_FRect m_DestRect;
	SDL_Rect m_SrcRect;

private:

	Vector2 _Vector2;

};

