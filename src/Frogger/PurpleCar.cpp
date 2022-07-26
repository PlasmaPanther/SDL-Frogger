#include "PurpleCar.h"
#include "../TimerModule.h"

void PurpleCar::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_Texture2D.LoadClippedTexture("frogger_sprites.png", 10, 267, m_Position, 28, 20, Vector2(1.8f, 1.6f));

	m_Velocity = { -40.0f, 0.0f };
}

void PurpleCar::Update()
{
	m_Texture2D.Move(m_Velocity * TimerModule::GetDelta());

	if (m_Texture2D.GetRect().x <= -45) {
		m_Texture2D.GetRect().x = 845;
	}

}

void PurpleCar::Render()
{
	m_Texture2D.RenderClippedTexture();
}