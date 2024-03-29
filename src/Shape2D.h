#pragma once
#include "Graphics.h"
#include "Math.h"
#include "Object2D.h"

struct Circle
{
	float x, y;
	float radius;

};

class Shape2D : public Object2D
{
public:
	Shape2D();
	~Shape2D() = default;

	//Places circle
	void Place(Vector2 _pos, float _radius);

	//Places Rectangle
	void Place(Vector2 _pos, Vector2 _scale);

	void PlaceLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	void RenderRect(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool renderFlag = true);
	void RenderCircle(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, bool renderFlag = true);

	void Move(Vector2 _vec);

	void Kill();

	Circle& GetCircle();

private:

	Circle m_Circle;

	float m_Radius;

};

