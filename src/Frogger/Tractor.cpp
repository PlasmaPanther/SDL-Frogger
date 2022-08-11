#include "Tractor.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void Tractor::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_AnimatedTexture.LoadAnimation("frogger_sprites.png", m_Position, 24, 21, 0, Vector2(1.8f, 1.6f));

	m_Velocity = { 30.0f, 0.0f };

	CollisionManager::AddCollider(&m_AnimatedTexture, "vehicles");
}

void Tractor::Update()
{
	m_AnimatedTexture.Move(m_Velocity * TimerModule::GetDelta());

	if (m_AnimatedTexture.GetRect().x >= 845) {
		m_AnimatedTexture.GetRect().x = -45;
	}
}

void Tractor::Render()
{
	m_AnimatedTexture.RenderAnimation(35, 305, 600, 3, 0);
}