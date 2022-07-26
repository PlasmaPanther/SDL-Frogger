#include "Turtle.h"
#include "../TimerModule.h"

void Turtle::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_AnimatedTexture.LoadAnimation("frogger_sprites.png", m_Position, 30, 22, 0, Vector2(1.5f, 1.5f));

	m_Velocity = { -65.0f, 0.0f };
}

void Turtle::Update()
{

	m_AnimatedTexture.Move(m_Velocity * TimerModule::GetDelta());

	if (m_AnimatedTexture.GetRect().x <= -60) {
		m_AnimatedTexture.GetRect().x = 860;
	}
}

void Turtle::Render(TurtleAnimation animationType)
{
	switch (animationType) {

		case TurtleAnimation::SHORT:
			m_AnimatedTexture.RenderAnimation(35, 394, 800, 3, 0);
			break;

		case TurtleAnimation::LONG:
			m_AnimatedTexture.RenderAnimation(35, 394, 800, 6, 0);

			if (m_AnimatedTexture.GetCurrentFrame() == 5) {
				m_AnimatedTexture.RenderAnimation(35, 394, 800, 2, 2);
			}

			break;

		default:
			break;
	}
}
