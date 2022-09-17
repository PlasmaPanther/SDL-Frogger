#pragma once
#include <vector>
#include <array>
#include <utility>

#include "../AnimatedTexture2D.h"
#include "../Shape2D.h"
#include "../AudioPlayer.h"
#include "../Font.h"

enum class Status { NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, DEAD = 5};

class Frog
{
public:

	void Init(Vector2 _pos);

	void Update();

	void Render();

	void Clean();

	//These functions will help with rendering the frogs at the splash menu
	void EntranceRender(bool inHorizontalPos = false, bool AllInPosition = false, bool renderFlag = true);
	void Move(Vector2 _vel) { m_FrogTexture.Move(_vel); m_AnimatedFrogTexture.Move(_vel); m_Position += _vel; }
	Vector2 GetPosition() { return m_Position; }
	//======================================================================

	int GetScore() const;

private:

	Status m_FrogStatus;

	AnimatedTexture2D m_AnimatedFrogTexture;
	Texture2D m_FrogTexture;

	AudioPlayer m_Hop;
	AudioPlayer m_RunOver;
	AudioPlayer m_Drown;
	AudioPlayer m_LowTime;
	AudioPlayer m_Extra;

	Font m_BlackBoxText;

	std::vector<Texture2D> m_HomeTextures;
	std::vector<std::pair<Texture2D, bool>> m_FrogLivesTextures;

	std::array<bool, 5> m_IsHome;

	Vector2 m_Velocity;
	Vector2 m_Position;
	Vector2 m_StartingPosition;

	Shape2D m_TimerBox;
	Shape2D m_BlackBox;

	int m_Score;
	int m_FrogLives;

	float m_BlackBoxTimer;
	float m_BlackBoxMaxTime;

	bool m_BlackBoxRenderFlag;
	bool m_Dead;

	float m_TimeRemaining;
};

