#include "Log.h"
#include "../TimerModule.h"
#include "../CollisionManager.h"
#include "Frog.h"

void Log::Init(Vector2 _pos, LogType type)
{
	m_Position = _pos;
	m_Type = type;

	switch (type) {

		case LogType::SHORT:
			m_LogTexture.LoadClippedTexture("frogger_sprites.png", 7, 229, m_Position, 84, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 40.0f, 0.0f };

			CollisionManager::AddCollider(&m_LogTexture, "short_logs");
			break;

		case LogType::MEDIUM:
			m_LogTexture.LoadClippedTexture("frogger_sprites.png", 7, 197, m_Position, 116, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 65.0f, 0.0f };

			CollisionManager::AddCollider(&m_LogTexture, "medium_logs");
			break;

		case LogType::LONG:
			m_LogTexture.LoadClippedTexture("frogger_sprites.png", 7, 165, m_Position, 177, 23, Vector2(1.5f, 1.5f));
			m_Velocity = { 80.0f, 0.0f };

			CollisionManager::AddCollider(&m_LogTexture, "long_logs");
			break;

		default:
			break;
	}
}

void Log::Update()
{
	m_LogTexture.Move(m_Velocity * TimerModule::GetDelta());

	switch (m_Type) {

	case LogType::SHORT:
		
		if (m_LogTexture.GetRect().x >= 830) {
			m_LogTexture.GetRect().x = -130;
		}

		break;

	case LogType::MEDIUM:
		
		if (m_LogTexture.GetRect().x >= 850) {
			m_LogTexture.GetRect().x = -170;
		}

		break;

	case LogType::LONG:

		if (m_LogTexture.GetRect().x >= 870) {
			m_LogTexture.GetRect().x = -260;
		}

		break;

	default:
		m_Type = LogType::NONE;
		break;
	}

}

void Log::Render()
{
	m_LogTexture.RenderClippedTexture();
}

void Log::Clean()
{

	switch (m_Type) {

	case LogType::SHORT:

		CollisionManager::RemoveCollider("short_logs");

		break;

	case LogType::MEDIUM:

		CollisionManager::RemoveCollider("medium_logs");

		break;

	case LogType::LONG:

		CollisionManager::RemoveCollider("long_logs");

		break;

	default:
		break;
	}

}
