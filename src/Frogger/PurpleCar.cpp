#include "PurpleCar.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void PurpleCar::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_PurpleCarTexture.LoadClippedTexture("frogger_sprites.png", 10, 267, m_Position, 28, 20, Vector2(1.8f, 1.6f));

	m_Velocity = { -40.0f, 0.0f };

	CollisionManager::AddCollider(&m_PurpleCarTexture, "vehicles");
}

void PurpleCar::Update()
{
	m_PurpleCarTexture.Move(m_Velocity * TimerModule::GetDelta());

	if (m_PurpleCarTexture.GetRect().x <= -45) {
		m_PurpleCarTexture.GetRect().x = 845;
	}

}

void PurpleCar::Render()
{
	m_PurpleCarTexture.RenderClippedTexture();
}

void PurpleCar::Clean()
{
	CollisionManager::RemoveCollider("vehicles");
}
