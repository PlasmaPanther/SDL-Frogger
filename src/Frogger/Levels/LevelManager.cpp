#include "LevelManager.h"

void LevelManager::AddLevel(Level* level)
{
	s_LevelVector.push_back(level);
	s_LevelVector.back()->Init();
}

void LevelManager::SwitchLevel(Level* level)
{
	if (!s_LevelVector.empty()) {
		s_LevelVector.back()->Clean();
		s_LevelVector.pop_back();
	}

	AddLevel(level);

}

void LevelManager::Update()
{
	if (!s_LevelVector.empty()) {
		s_LevelVector.back()->Update();
	}
}

void LevelManager::Render()
{
	if (!s_LevelVector.empty()) {
		s_LevelVector.back()->Render();
	}
}

void LevelManager::Clean()
{
	if (!s_LevelVector.empty()) {
		s_LevelVector.back()->Clean();
	}
}

void LevelManager::RemoveLevel()
{
	if (!s_LevelVector.empty()) {
		s_LevelVector.back()->Clean();
		s_LevelVector.pop_back();
	}
}
