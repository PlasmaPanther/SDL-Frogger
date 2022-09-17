#include "Turtle.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"

void Turtle::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_AnimatedTurtleTexture.LoadAnimation("frogger_sprites.png", m_Position, 30, 22, 0, Vector2(1.5f, 1.5f));

	m_Velocity = { -65.0f, 0.0f };

	CollisionManager::AddCollider(&m_AnimatedTurtleTexture, "turtles");
}

void Turtle::Update()
{

	m_AnimatedTurtleTexture.Move(m_Velocity * TimerModule::GetDelta());

	if (m_AnimatedTurtleTexture.GetRect().x <= -60) {
		m_AnimatedTurtleTexture.GetRect().x = 860;
	}
}

void Turtle::Render(TurtleAnimation animationType)
{
	switch (animationType) {

		case TurtleAnimation::SHORT:
			m_AnimatedTurtleTexture.RenderAnimation(35, 394, 800, 3, 0);
			break;

		case TurtleAnimation::LONG:
			m_AnimatedTurtleTexture.RenderAnimation(35, 394, 800, 6, 0);

			if (m_AnimatedTurtleTexture.GetCurrentFrame() == 5) {
				m_AnimatedTurtleTexture.RenderAnimation(35, 394, 800, 2, 2);
			}

			break;

		default:
			break;
	}
}

void Turtle::Clean()
{
	CollisionManager::RemoveCollider("turtles");
}

Vector2 Turtle::GetVelocity() const
{
	return m_Velocity;
}
