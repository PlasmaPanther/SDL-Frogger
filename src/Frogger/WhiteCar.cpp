#include "WhiteCar.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void WhiteCar::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_WhiteCarTexture.LoadClippedTexture("frogger_sprites.png", 45, 265, m_Position, 27, 24, Vector2(1.8f, 1.5f));

	m_Velocity = { 70.0f, 0.0f };
	
	CollisionManager::AddCollider(&m_WhiteCarTexture, "vehicles");
}

void WhiteCar::Update()
{
	m_WhiteCarTexture.Move(m_Velocity * TimerModule::GetDelta());

	if (m_WhiteCarTexture.GetRect().x >= 845) {
		m_WhiteCarTexture.GetRect().x = -45;
	}
}

void WhiteCar::Render()
{
	m_WhiteCarTexture.RenderClippedTexture();
}

void WhiteCar::Clean()
{
	CollisionManager::RemoveCollider("vehicles");
}
