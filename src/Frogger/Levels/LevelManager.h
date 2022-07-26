#pragma once
#include <vector>

#include "Level.h"

class LevelManager
{
public:

	static void AddLevel(Level* level);

	static void SwitchLevel(Level* level);

	void Update();

	void Render();

	void Clean();

	static void RemoveLevel();

private:

	static inline std::vector<Level*> s_LevelVector;

};

