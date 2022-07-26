#include "WhiteCar.h"
#include "../TimerModule.h"

void WhiteCar::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_Texture2D.LoadClippedTexture("frogger_sprites.png", 45, 265, m_Position, 27, 24, Vector2(1.8f, 1.5f));

	m_Velocity = { 51.0f, 0.0f };
}

void WhiteCar::Update()
{
	m_Texture2D.Move(m_Velocity * TimerModule::GetDelta());

	if (m_Texture2D.GetRect().x >= 845) {
		m_Texture2D.GetRect().x = -45;
	}
}

void WhiteCar::Render()
{
	m_Texture2D.RenderClippedTexture();
}
