#include "Frog.h"
#include "../Input.h"
#include "../CollisionManager.h"

void Frog::Init(Vector2 _pos)
{
	m_Position = _pos;

	m_AnimatedTexture.LoadAnimation("frogger_sprites.png", m_Position, 32, 24, 0, Vector2(1.5f, 1.5f));
	m_Texture2D.LoadClippedTexture("frogger_sprites.png", 0, 365, m_Position, 23, 17, Vector2(1.35f, 1.5f));
	
	m_FrogDirections = Directions::UP;

	CollisionManager::AddCollider(&m_Texture2D, "player");
}

void Frog::Update()
{
	if (CollisionManager::CheckGroupCollision("player", "vehicles")) {
		
	}

	if (CollisionManager::CheckGroupCollision("player", "logs")) {
		
	}

	if (CollisionManager::CheckGroupCollision("player", "turtles")) {
		
	}

	if (Input::KeyPressed(SDL_SCANCODE_W)) {
		m_FrogDirections = Directions::UP;
		m_Texture2D.Move(Vector2(0, -38.3f));
		
	}
	
	if (Input::KeyPressed(SDL_SCANCODE_S)) {
		m_FrogDirections = Directions::DOWN;
		m_Texture2D.Move(Vector2(0, 38.3f));

	}

	if (Input::KeyPressed(SDL_SCANCODE_A)) {
		m_FrogDirections = Directions::LEFT;
		m_Texture2D.Move(Vector2(-30, 0));
	}

	if (Input::KeyPressed(SDL_SCANCODE_D)) {
		m_FrogDirections = Directions::RIGHT;
		m_Texture2D.Move(Vector2(30, 0));
	}
}

void Frog::Render()
{

	switch (m_FrogDirections) {
	
		case Directions::UP:
			m_Texture2D.RenderClippedTexture();
			break;

		case Directions::DOWN:
			m_Texture2D.RenderClippedTexture(180.0f); //rotate 180 degrees
			break;

		case Directions::LEFT:
			m_Texture2D.RenderClippedTexture(-90.0f);
			break;

		case Directions::RIGHT:
			m_Texture2D.RenderClippedTexture(90.0f);
			break;
	
		default:
			break;
	}

}

void Frog::EntranceRender(bool inHorizontalPos, bool AllInPosition, bool renderFlag)
{
	if (renderFlag) {

		if (inHorizontalPos) { //checks to see if a frog is in position
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