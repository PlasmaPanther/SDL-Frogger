#include "Shape2D.h"
#include <iostream>

Shape2D::Shape2D() {
	m_Rect = { 0, 0, 0, 0 };
	m_Circle = { 0, 0, 0 };
	m_Velocity = { 0, 0 };
}

void Shape2D::PlaceRect(Vector2 _pos, int width, int height) {
	m_Rect.x = _pos.x;
	m_Rect.y = _pos.y;
	m_Rect.w = width;
	m_Rect.h = height;
}

void Shape2D::DrawRect(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(Graphics::GetRenderer(), r, g, b, a); //Sets rect color
	SDL_RenderDrawRect(Graphics::GetRenderer(), &m_Rect);
	SDL_RenderFillRect(Graphics::GetRenderer(), &m_Rect);
}

void Shape2D::PlaceCircle(Vector2 _pos, int radius) {
	m_Circle.x = _pos.x;
	m_Circle.y = _pos.y;
	m_Circle.radius = radius;
}

void Shape2D::DrawCircle(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

	SDL_SetRenderDrawColor(Graphics::GetRenderer(), r, g, b, a); //sets circle color

	for (int y = 0; y < m_Circle.radius; ++y)
	{
		float x_point = sqrtf((m_Circle.radius * m_Circle.radius) - (y * y)); //Calculating the X point using the Pythagorean theorem for circles

		SDL_RenderDrawLine(Graphics::GetRenderer(), m_Circle.x - x_point, m_Circle.y - y, m_Circle.x + x_point, m_Circle.y - y); //Draws the top half
		SDL_RenderDrawLine(Graphics::GetRenderer(), m_Circle.x - x_point, m_Circle.y + y, m_Circle.x + x_point, m_Circle.y + y); //Draws the bottom half

	}

}

//very bad and unstable don't use yet
void Shape2D::DrawTriangle(int x, int y) {
	for (int i = 100; i > 0; --i) {
		SDL_RenderDrawLine(Graphics::GetRenderer(), x, y, y - i - 50, x + 200);
	}

	/*for (int i = 0; i < 100; ++i) { //RHOMBUS
			SDL_RenderDrawLine(Graphics::GetRenderer(), 200 + i, 300 - i, 300 + i, 200 * 2 - i);
	}*/
}

void Shape2D::MoveRect(Vector2 _vel) {
	m_Rect.x += _vel.x;
	m_Rect.y += _vel.y;
}

void Shape2D::MoveCircle(Vector2 _vel) {
	m_Circle.x += _vel.x;
	m_Circle.y += _vel.y;
}

void Shape2D::PlaceLine(float x1, float y1, float x2, float y2)
{
	SDL_SetRenderDrawColor(Graphics::GetRenderer(), 255, 200, 100, 255);
	SDL_RenderDrawLineF(Graphics::GetRenderer(), x1, y1, x2, y2);
}

void Shape2D::RenderLine()
{

}

bool Shape2D::RectangleCollision(SDL_Rect* recta, SDL_Rect* rectb) {
	if (SDL_HasIntersection(recta, rectb)) {
		return true;
	}

	return false;
}

bool Shape2D::CircleCollision(Circle* circlea, Circle* circleb) {
	float deltaX = circlea->x - circleb->x;
	float deltaY = circlea->y - circleb->y;

	float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

	int totalRadius = circlea->radius + circleb->radius;

	if (distance < totalRadius) {
		return true;
	}

	return false;
}

bool Shape2D::CircleToRectCollision(Circle* _circle, SDL_Rect* rect) {
	float testX = _circle->x;
	float testY = _circle->y;

	// which edge is closest?
	if (_circle->x < rect->x) {
		testX = rect->x; // test left edge
	}
	else if (_circle->x > rect->x + rect->w) {
		testX = rect->x + rect->w; // right edge
	}

	if (_circle->y < rect->y) {
		testY = rect->y; // top edge
	}
	else if (_circle->y > rect->y + rect->h) {
		testY = rect->y + rect->h; // bottom edge
	}

	// get distance from closest edges
	float distanceX = _circle->x - testX;
	float distanceY = _circle->y - testY;
	float distance = sqrtf((distanceX * distanceX) + (distanceY * distanceY));

	// if the distance is less than the radius, collision!
	if (distance <= _circle->radius) {
		return true;
	}

	return false;
}

void Shape2D::SetSpeed(Vector2 _vel) {
	m_Velocity = _vel;
}

Vector2 Shape2D::GetSpeed() {
	return m_Velocity;
}

void Shape2D::Kill() {
	m_Rect = { 0, 0, 0, 0 };
	m_Circle = { 0, 0, 0 };
}

SDL_Rect* Shape2D::GetRect() {
	return &m_Rect;
}

Circle* Shape2D::GetCircle() {
	return &m_Circle;
}