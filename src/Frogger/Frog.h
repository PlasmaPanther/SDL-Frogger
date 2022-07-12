#pragma once
#include "FroggerEntity.h"

class Frog: public FroggerEntity
{
public:

	void Init(Vector2 _pos) override;

	void Update() override;
	void Render(bool renderFlag = true);
	void Render(bool renderFlag = true, bool HorizontalPos = false, bool AllInPosition = false);

	void Entrance();

	void Clean() override;

private:

};

