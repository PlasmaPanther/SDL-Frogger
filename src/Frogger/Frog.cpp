#include "Frog.h"

void Frog::Init(Vector2 _pos)
{
	m_Position = _pos;
	m_AnimatedTexture.LoadAnimation("frogger_spritesF.png", m_Position, 33, 25, 0, Vector2(1.5f, 1.5f));
	//m_AnimatedTexture.LoadEx("c.png", m_Position);
}

void Frog::Update()
{

}

void Frog::Render(bool renderFlag)
{
	m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0);
}

void Frog::Render(bool renderFlag, bool HorizontalPos, bool AllInPosition)
{
	if (renderFlag) {
		if (HorizontalPos) {
			m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0, !AllInPosition);

			if (AllInPosition) {
				m_AnimatedTexture.RenderAnimation(35, 366, 300, 2, 0);
			}

		}
		else {
			m_AnimatedTexture.RenderAnimation(35, 337, 300, 2, 2);
		}
	}

}

void Frog::Entrance()
{
	
}

void Frog::Clean()
{
	
}
