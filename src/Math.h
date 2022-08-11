#pragma once
#include <cmath>

constexpr float PI = 3.14159265f;
constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;

struct Vector2 {
	float x, y;
	
	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	Vector2& operator += (const Vector2& rightside) {
		
		x += rightside.x;
		y += rightside.y;

		return *this;
	}

	Vector2& operator -= (const Vector2& leftside) {

		x -= leftside.x;
		y -= leftside.y;

		return *this;
	}

};

inline Vector2 operator +(const Vector2& leftside, const Vector2& rightside) {
	return Vector2(leftside.x + rightside.x, leftside.y + rightside.y);
}

inline Vector2 operator -(const Vector2& leftside, const Vector2& rightside) {
	return Vector2(leftside.x - rightside.x, leftside.y - rightside.y);
}

inline Vector2 operator *(const Vector2& leftside, const float& rightside) {
	return Vector2(leftside.x * rightside, leftside.y * rightside);
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };