#pragma once
#include "FroggerEntity.h"

enum class Directions { NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4};

class Frog: public FroggerEntity
{
public:

	void Init(Vector2 _pos) override;

	void Update() override;

	void Render() override;

	//This function will help with rendering the frogs at the splash menu
	void EntranceRender(bool HorizontalPos = false, bool AllInPosition = false, bool renderFlag = true);

	void Clean() override;

private:

	Directions m_FrogDirections;

};

