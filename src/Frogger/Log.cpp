#include "Log.h"
#include "../TimerModule.h"

void Log::Init(Vector2 _pos, LogType type)
{
	m_Position = _pos;
	m_Type = type;

	switch (type) {

		case LogType::SHORT:
			m_Texture.LoadClippedTexture("frogger_sprites.png", 7, 229, m_Position, 84, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 40.0f, 0.0f };
			break;

		case LogType::MEDIUM:
			m_Texture.LoadClippedTexture("frogger_sprites.png", 7, 197, m_Position, 116, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 55.0f, 0.0f };
			break;

		case LogType::LONG:
			m_Texture.LoadClippedTexture("frogger_sprites.png", 7, 165, m_Position, 177, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 70.0f, 0.0f };
			break;

		default:
			break;
	}

}

void Log::Update()
{
	m_Texture.Move(m_Velocity * TimerModule::GetDelta());

	switch (m_Type) {

	case LogType::SHORT:
		
		if (m_Texture.GetRect().x >= 830) {
			m_Texture.GetRect().x = -130;
		}

		break;

	case LogType::MEDIUM:
		
		if (m_Texture.GetRect().x >= 850) {
			m_Texture.GetRect().x = -170;
		}
		
		break;

	case LogType::LONG:

		if (m_Texture.GetRect().x >= 870) {
			m_Texture.GetRect().x = -260;
		}
		
		break;

	default:
		break;
	}

}

void Log::Render()
{
	m_Texture.RenderClippedTexture();
}
