#pragma once
#include "Graphics.h"
#include "Math.h"

struct Circle
{
	int x, y;
	int radius;

};

class Shape2D
{
public:
	Shape2D();
	~Shape2D() = default;

	void PlaceRect(Vector2 _pos, int width, int height);
	void DrawRect(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	
	void PlaceCircle(Vector2 _pos, int radius);
	void DrawCircle(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void DrawTriangle(int x, int y);

	void MoveRect(Vector2 _vel);
	void MoveCircle(Vector2 _vel);

	bool RectangleCollision(SDL_Rect* recta, SDL_Rect* rectb);
	bool CircleCollision(Circle* circlea, Circle* circleb);
	bool CircleToRectCollision(Circle* _circle, SDL_Rect* rect);

	void SetSpeed(Vector2 _vel);
	Vector2 GetSpeed();

	void Kill();

	SDL_Rect* GetRect();
	
	Circle* GetCircle();

private:

	SDL_Rect m_Rect;

	Circle m_Circle;

	Vector2 m_Velocity;

};

