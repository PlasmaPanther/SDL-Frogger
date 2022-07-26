#pragma once
#include "../Texture2D.h"

enum class LogType { NONE = 0, SHORT = 1, MEDIUM = 2, LONG = 3 };

class Log
{
public:

	void Init(Vector2 _pos, LogType type = LogType::NONE);

	void Update();

	void Render();

private:

	Vector2 m_Position;
	Vector2 m_Velocity;

	Texture2D m_Texture;

	LogType m_Type;

};

