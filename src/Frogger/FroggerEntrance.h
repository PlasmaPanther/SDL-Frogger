#pragma once
#include <vector>
#include <array>
#include "Frog.h"

class FroggerEntrance
{
public:
	FroggerEntrance() = default;
	~FroggerEntrance() = default;

	void Init(Vector2 _pos);

	void Update();

	void Render();

	void Clean();

private:

	static inline std::vector<Frog> m_FrogVector;
	std::vector<Texture2D> m_Letters;

	static inline std::array<bool, 7> m_InPositionHorizontal;
	static inline std::array<bool, 7> m_InPositionVertical;
	std::array<bool, 7> m_RenderedLetters;

	bool m_AllInPositionHorizontal;
	int j = 1;
};

