#include "Frog.h"
#include "../Input.h"

void Frog::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_AnimatedTexture.LoadAnimation("frogger_spritesF.png", m_Position, 33, 25, 0, Vector2(1.5f, 1.5f));
	
	m_FrogDirections = Directions::UP;
}

void Frog::Update()
{
	if (Input::KeyPressed(SDL_SCANCODE_W)) {
		m_FrogDirections = Directions::UP;
		m_AnimatedTexture.Move(Vector2(0, -37.5f));
	}
	
	if (Input::KeyPressed(SDL_SCANCODE_S)) {
		m_FrogDirections = Directions::DOWN;
		m_AnimatedTexture.Move(Vector2(0, 37.5f));
	}

	if (Input::KeyPressed(SDL_SCANCODE_A)) {
		m_FrogDirections = Directions::LEFT;
		m_AnimatedTexture.Move(Vector2(-38, 0));
	}

	if (Input::KeyPressed(SDL_SCANCODE_D)) {
		m_FrogDirections = Directions::RIGHT;
		m_AnimatedTexture.Move(Vector2(38, 0));
	}
}

void Frog::Render()
{

	switch (m_FrogDirections) {
	
		case Directions::UP:
			m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0);
			break;

		case Directions::DOWN:
			m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 2);
			break;

		case Directions::LEFT:
			m_AnimatedTexture.RenderAnimation(35, 336, 300, 1, 2);
			break;

		case Directions::RIGHT:
			m_AnimatedTexture.RenderAnimation(35, 336, 300, 1, 0);
			break;
	
		default:
			break;
	}

}

void Frog::EntranceRender(bool HorizontalPos, bool AllInPosition, bool renderFlag)
{
	if (renderFlag) {

		if (HorizontalPos) { //checks to see if a frog is in position
			m_AnimatedTexture.RenderAnimation(35, 366, 300, 1, 0, SDL_FLIP_NONE, !AllInPosition); //render standing frog

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
