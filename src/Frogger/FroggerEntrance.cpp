#include "FroggerEntrance.h"

void FroggerEntrance::Init(Vector2 _pos)
{
	if (m_FrogVector.size() != 7) {
		m_FrogVector.resize(7);
	}

	for (int i = 0; i < m_FrogVector.size(); ++i) {
		m_FrogVector[i].Init(_pos);
	}

	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 13, 10, Vector2(138, 120), 32, 32, 1.0f);  //F
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 60, 10, Vector2(220, 120), 32, 32, 1.0f);  //R
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 110, 10, Vector2(300, 120), 32, 32, 1.0f); //O
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 157, 10, Vector2(380, 120), 32, 32, 1.0f); //G
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 157, 10, Vector2(460, 120), 32, 32, 1.0f); //G
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 257, 10, Vector2(540, 120), 32, 32, 1.0f); //E
	m_Letters.emplace_back().LoadClippedTexture("frogger_spritesF.png", 300, 10, Vector2(620, 120), 32, 32, 1.0f); //R

	m_InPositionHorizontal.fill(false);
	m_InPositionVertical.fill(false);
	m_RenderedLetters.fill(false);

	m_AllInPositionHorizontal = false;
}

void FroggerEntrance::Update()
{
	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (!m_InPositionHorizontal[i]) {

			m_FrogVector[i].Move(Vector2(-1.3f, 0));

			if (m_FrogVector[i].GetPosition().x <= 140 + (i * 80)) {
				m_InPositionHorizontal[i] = true;
			}

			if (i == 6 && m_InPositionHorizontal[i]) { //check to see if the last frog is in position
				
				m_AllInPositionHorizontal = true;
			}

			return; //Goes to the beggining of the current iteration
		}

	}

	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (m_InPositionHorizontal[i]) {

			if (!m_InPositionVertical[i]) {

				m_FrogVector[i].Move(Vector2(0, -1));

				if (m_FrogVector[i].GetPosition().y == 120) {
					m_InPositionVertical[i] = true;
				}

			}
		}
	}

}

void FroggerEntrance::Render()
{
	for (int i = 0; i < m_FrogVector.size(); ++i) {

		if (m_InPositionVertical[i]) {

			m_Letters[i].RenderClippedTexture();

			if (!m_RenderedLetters[i]) {

				while (j < m_FrogVector.size()) {

					for (int k = j; k < m_FrogVector.size(); ++k) { //re-render the frogs again since they disappear once they reach the top

						m_FrogVector[k].Render(true, m_InPositionHorizontal[i], m_AllInPositionHorizontal);

					}

					++j;
					break;
				}

				m_Letters[i].RenderClippedTexture();
				m_RenderedLetters[i] = true;

				SDL_Delay(500);

				return;
			}
			
		}
		else {
			m_FrogVector[i].Render(true, m_InPositionHorizontal[i], m_AllInPositionHorizontal);
		}
	}

}

void FroggerEntrance::Clean()
{

}
