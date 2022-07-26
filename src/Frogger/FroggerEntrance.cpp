#include "FroggerEntrance.h"
#include "../Input.h"
#include "../States/PlayState.h"
#include "../States/StateMachine.h"

void FroggerEntrance::Init(Vector2 _pos)
{

	m_FrogVector.resize(7);

	for (int i = 0; i < m_FrogVector.size(); ++i) {
		m_FrogVector[i].Init(_pos);
	}

	m_LettersVector.resize(7);

	m_LettersVector[0].LoadClippedTexture("frogger_sprites.png", 13,  10, Vector2(140, 90), 32, 32, 1.5f); //F
	m_LettersVector[1].LoadClippedTexture("frogger_sprites.png", 60,  10, Vector2(220, 90), 32, 32, 1.5f); //R
	m_LettersVector[2].LoadClippedTexture("frogger_sprites.png", 110, 10, Vector2(300, 90), 32, 32, 1.5f); //O
	m_LettersVector[3].LoadClippedTexture("frogger_sprites.png", 157, 10, Vector2(380, 90), 32, 32, 1.5f); //G
	m_LettersVector[4].LoadClippedTexture("frogger_sprites.png", 157, 10, Vector2(460, 90), 32, 32, 1.5f); //G
	m_LettersVector[5].LoadClippedTexture("frogger_sprites.png", 257, 10, Vector2(540, 90), 32, 32, 1.5f); //E
	m_LettersVector[6].LoadClippedTexture("frogger_sprites.png", 300, 10, Vector2(620, 90), 32, 32, 1.5f); //R

	m_TextVector.resize(7);

	m_TextVector[0].Load("Emulogic.ttf", Vector2(160, 220), 24, "10 pts for each step", Colors::YELLOW);
	m_TextVector[1].Load("Emulogic.ttf", Vector2(160, 270), 24, "50 pts for every frog", Colors::YELLOW);
	m_TextVector[2].Load("Emulogic.ttf", Vector2(160, 300), 24, "arrived home safely", Colors::RED);
	m_TextVector[3].Load("Emulogic.ttf", Vector2(160, 340), 24, "1000 pts by saving frogs", Colors::YELLOW);
	m_TextVector[4].Load("Emulogic.ttf", Vector2(160, 370), 24, "into five homes", Colors::RED);
	m_TextVector[5].Load("Emulogic.ttf", Vector2(160, 410), 24, "plus bonus", Colors::YELLOW);
	m_TextVector[6].Load("Emulogic.ttf", Vector2(155, 440), 24, "10 pts X remaining second", Colors::RED);

	m_ScoreRankingVector.resize(5);

	m_ScoreRankingVector[0].Load("Emulogic.ttf", Vector2(220, 240), 25, "1 st  04630 pts", Colors::WHITE);
	m_ScoreRankingVector[1].Load("Emulogic.ttf", Vector2(220, 290), 25, "2 nd  02050 pts", Colors::WHITE);
	m_ScoreRankingVector[2].Load("Emulogic.ttf", Vector2(220, 340), 25, "3 rd  01970 pts", Colors::WHITE);
	m_ScoreRankingVector[3].Load("Emulogic.ttf", Vector2(220, 390), 25, "4 th  01580 pts", Colors::PURPLE);
	m_ScoreRankingVector[4].Load("Emulogic.ttf", Vector2(220, 440), 25, "5 th  01270 pts", Colors::WHITE);

	m_InPositionHorizontal.fill(false);
	
	m_InPositionVertical.fill(false);
	m_RenderedLetters.fill(false);

	m_PointTable.Load("Emulogic.ttf", 24, "--Point Table--", Colors::WHITE);
	m_Konami.Load("Emulogic.ttf", 24, "Konami  ©  1981", Colors::WHITE);

	m_ScoreRanking.Load("Emulogic.ttf", 24, "Score ranking", Colors::YELLOW);

	m_InsertCoin.Load("Emulogic.ttf", 24, "Insert coin", Colors::GREEN);
	m_FrogsPerPlayer.Load("Emulogic.ttf", 24, "3 frogs per player", Colors::YELLOW);

	m_AllInPositionHorizontal = false;
	
	m_FrogAnimationDone = false;
	m_TextAnimationDone = false;

	m_ShowScoreRanking = false;
	m_InsertedCoin = false;

	m_RenderTracker = 1;
}

void FroggerEntrance::Update()
{

	if (Input::KeyPressed(SDL_SCANCODE_RETURN)){
		this->SkipScene();
	}

	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (!m_InPositionHorizontal[i]) {

			m_FrogVector[i].Move(Vector2(-1.3f, 0));

			if (m_FrogVector[i].GetPosition().x <= 140 + (i * 80)) {
				m_InPositionHorizontal[i] = true;
			}

			if (i == 6 && m_InPositionHorizontal[i]) { //check to see if the last frog is in position
				
				m_AllInPositionHorizontal = true;
			}

			return; //Exit the for loop and the function altogether
		}

	}

	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (m_InPositionHorizontal[i] && !m_InPositionVertical[i]) {

			m_FrogVector[i].Move(Vector2(0, -1));

			if (m_FrogVector[i].GetPosition().y == 100) {
				m_InPositionVertical[i] = true;
			}

		}
	}

}

void FroggerEntrance::Render()
{
	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (m_InPositionVertical[i]) { //check frog position

			m_LettersVector[i].RenderClippedTexture();

			if (!m_RenderedLetters[i]) { //check to see if the frogs have turned into letters

				while (m_RenderTracker < m_FrogVector.size()) {

					for (int j = m_RenderTracker; j < m_FrogVector.size(); ++j) { //re-render the frogs again since they disappear once they reach the top

						m_FrogVector[j].EntranceRender(m_InPositionHorizontal[j], m_AllInPositionHorizontal);

					}

					++m_RenderTracker; //re-render frogs staring from the next one
					break;
				}

				m_RenderedLetters[i] = true;

				SDL_Delay(700);

				if (i == 6) {
					m_FrogAnimationDone = true;
					m_RenderTracker = 0;
				}

				return;
			}
			
		}
		else {
			m_FrogVector[i].EntranceRender(m_InPositionHorizontal[i], m_AllInPositionHorizontal); //render walking animation
		}
	}

	m_Konami.Render(Vector2(220, 520), m_FrogAnimationDone); //render the konami logo when the frog animation is done

	if (m_FrogAnimationDone && !m_TextAnimationDone) {
		
		m_PointTable.Render(Vector2(220, 180));
		
		if (m_RenderTracker != 7) {

			while (m_RenderTracker < m_TextVector.size()) {

				m_TextVector[m_RenderTracker].Render();

				m_RenderTracker++;

				SDL_Delay(800); //have the text appear ~1 second after the previous one

				break;
			}
		
		}
		else {
			m_TextAnimationDone = true;
			m_RenderTracker = 0;
		}
		
		for (int i = 0; i < m_RenderTracker; ++i) {
			m_TextVector[i].Render();
		}
		
		if (m_TextAnimationDone) {
			SDL_Delay(3000); //keep the text for 3 seconds before it dissapears
			m_ShowScoreRanking = true;
		}
	}

	if (m_ShowScoreRanking) {
		
		m_ScoreRanking.Render(Vector2(220, 180));

		for (int i = 0; i < m_ScoreRankingVector.size(); ++i) {
			m_ScoreRankingVector[i].Render();
		}

		++m_RenderTracker;

		if (m_RenderTracker > 2) { //have the score stay on screen after the screen updates and the previous text disappears
								  //otherwise the old and new text will be rendered on top of eachother for a short time

			m_ShowScoreRanking = false;
			m_InsertedCoin = true;

			SDL_Delay(3000);
			m_RenderTracker = 0;
		}

	}
	
	if(m_InsertedCoin) {

		++m_RenderTracker;

		m_InsertCoin.Render(Vector2(250, 250));
		m_FrogsPerPlayer.Render(Vector2(220, 350));

		if (m_RenderTracker > 3) {

			SDL_Delay(3000);

			m_InsertedCoin = false;

			StateMachine::switchState(PlayState::GetInstance());
		}
	}
	
}

bool FroggerEntrance::IsAnimationDone()
{
	return m_FrogAnimationDone;
}

void FroggerEntrance::SkipScene()
{
	m_InPositionVertical.fill(true);
	m_RenderedLetters.fill(true);
	m_FrogAnimationDone = true;
	m_RenderTracker = 0;
}

void FroggerEntrance::Clean()
{
	m_FrogVector.clear();
	m_TextVector.clear();
	m_LettersVector.clear();

	m_InPositionHorizontal.fill(false);
	m_InPositionVertical.fill(false);
	m_RenderedLetters.fill(false);

	m_FrogAnimationDone = false;
	m_RenderTracker = 1;
}
