#pragma once
#include <vector>
#include <array>

#include "Frog.h"
#include "../Font.h"

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

	void SkipScene();
	void LoadResources();

private:

	std::vector<Frog> m_FrogVector;
	
	std::vector<Font> m_ScoreRankingVector;
	std::vector<Font> m_TextVector;
	
	std::vector<Texture2D> m_LettersVector;

	std::array<bool, 7> m_InPositionHorizontal;
	std::array<bool, 7> m_InPositionVertical;

	std::array<bool, 7> m_RenderedLetters;

	Font m_PointTableHandle;
	Font m_KonamiLogo;
	
	Font m_ScoreRankingHandle;
	
	Font m_InsertCoin;
	Font m_FrogsPerPlayer;

	bool m_FrogAnimationDone;
	bool m_TextAnimationDone;
	
	bool m_AllInPositionHorizontal;
	
	bool m_ShowScoreRanking;
	bool m_InsertedCoin;

	int m_RenderTracker;

	int m_TopCurrentScore;
	int m_PreviousTopScore;

	float m_CoinTimer;
};

