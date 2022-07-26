#pragma once

class Level {

public:

	virtual ~Level() = default;

	virtual void Init() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Clean() = 0;

};