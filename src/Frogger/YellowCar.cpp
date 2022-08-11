#include "YellowCar.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void YellowCar::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_Texture2D.LoadClippedTexture("frogger_sprites.png", 82, 264, m_Position, 24, 25, Vector2(1.8f, 1.3f));

	m_Velocity = { -30.0f, 0.0f };

	CollisionManager::AddCollider(&m_Texture2D, "vehicles");
}

void YellowCar::Update()
{
	m_Texture2D.Move(m_Velocity * TimerModule::GetDelta());

	if (m_Texture2D.GetRect().x <= -45) {
		m_Texture2D.GetRect().x = 845;
	}

}

void YellowCar::Render()
{
	m_Texture2D.RenderClippedTexture();
}