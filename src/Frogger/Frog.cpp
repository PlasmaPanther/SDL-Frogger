#include "Frog.h"

void Frog::Init(Vector2 _pos)
{
	m_Position = _pos;
	m_AnimatedTexture.LoadAnimation("frogger_spritesF.png", m_Position, 33, 25, 0, Vector2(1.5f, 1.5f));
}

void Frog::Update()
{

}

void Frog::Render()
{
	m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0);
}

void Frog::EntranceRender(bool HorizontalPos, bool AllInPosition, bool renderFlag)
{
	if (renderFlag) {

		if (HorizontalPos) { //checks to see if a frog is in position
			m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0, !AllInPosition); //render standing frog

			if (AllInPosition) { //check to see if all the frogs are in position
				m_AnimatedTexture.RenderAnimation(35, 366, 300, 2, 0); //play walking up animation
			}

		}
		else {
			m_AnimatedTexture.RenderAnimation(35, 337, 300, 2, 2); //play walking left animation
		}
	}
}

void Frog::Clean()
{
	
}
