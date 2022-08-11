#include "Truck.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void Truck::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_Texture2D.LoadClippedTexture("frogger_sprites.png", 109, 306, m_Position, 46, 19, Vector2(2.0f, 1.8f));

	m_Velocity = { -75.0f, 0.0f };

	CollisionManager::AddCollider(&m_Texture2D, "vehicles");
}

void Truck::Update()
{
	m_Texture2D.Move(m_Velocity * TimerModule::GetDelta());

	if (m_Texture2D.GetRect().x <= -93) {
		m_Texture2D.GetRect().x = 840;
	}

}

void Truck::Render()
{
	m_Texture2D.RenderClippedTexture();
}
