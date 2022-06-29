#include "ParticleEngine.h"
#include <cstdlib>
#include <time.h>

#pragma warning (disable : 4244) //disable conversion warnings

ParticleEngine::ParticleEngine() {
	m_Spawned = false;
	m_RandomizedSpeed = false;
	m_LimitedLife = false;

	m_ParticleWidth = 0;
	m_ParticleHeight = 0;

	m_StartingX = 0;
	m_StartingY = 0;
}

ParticleEngine::~ParticleEngine() {
	if (!m_ParticleVector.empty()) {
		m_ParticleVector.clear();
		m_ParticleVector.shrink_to_fit();
	}
}

void ParticleEngine::Render() {
	if (m_Spawned) {
		for (int i = 0; i < m_ParticleVector.size(); ++i) {
			if (m_ParticleVector[i].isAlive()) {
				m_ParticleVector[i].DrawRect(20 * i + 3, 34 * i + 50, 100 * i + 10, 255);
			}
		}
	}
}

void ParticleEngine::Update() {
	srand(time(0));

	if (m_Spawned) {
		if (m_RandomizedSpeed == false) {
			for (int i = 0; i < m_ParticleVector.size(); ++i) {

				//Randomize X and Y speeds
				int randomX = rand() % 6 + (-3);
				int randomY = rand() % 6 + (-3);

				if (randomX == 0) {
					randomX = 2; //make sure there are no idle particles
				}

				if (randomY == 0) {
					randomY = 2;
				}

				m_ParticleVector[i].SetSpeed(Vector2(randomX, randomY)); //apply randomized speed
				m_RandomizedSpeed = true;
			}
		}

		if (m_RandomizedSpeed) {
			for (int i = 0; i < m_ParticleVector.size(); ++i) {
				if (m_ParticleVector[i].isAlive()) {
					m_ParticleVector[i].MoveRect(m_ParticleVector[i].GetSpeed()); //Move particles by getting applied speed

					//Boundary check (if particles are outside the screen)
					if (m_ParticleVector[i].GetRect()->x > 800 || m_ParticleVector[i].GetRect()->x + m_ParticleVector[i].GetRect()->w < 0 || m_ParticleVector[i].GetRect()->y + m_ParticleVector[i].GetRect()->h < 0 || m_ParticleVector[i].GetRect()->y > 600) {
						m_ParticleVector[i].SetAliveStatus(false);
					}
				}
			}
		}

		if (m_LimitedLife && m_RandomizedSpeed) {
			for (int i = 0; i < m_ParticleVector.size(); ++i) {
				if (m_ParticleVector[i].isAlive()) {
					m_ParticleVector[i].LifetimeUpdate(); //check to see if a particle is near the end of its life; if it is set its status to dead
				}
			}
		}
	}
}

void ParticleEngine::Update(int x, int y) {
	//This function is the same as the one above except you can pass custom x, y values when particles respawns
	srand(time(0));

	if (m_Spawned) {
		if (m_RandomizedSpeed == false) {
			for (int i = 0; i < m_ParticleVector.size(); ++i) {

				//Randomize X and Y speeds
				int randomX = rand() % 6 + (-3);
				int randomY = rand() % 6 + (-3);

				m_ParticleVector[i].SetSpeed(Vector2(randomX, randomY)); //apply them
				m_RandomizedSpeed = true;
			}
		}

		if (m_RandomizedSpeed) {
			for (int i = 0; i < m_ParticleVector.size(); i++) {
				if (m_ParticleVector[i].isAlive()) {
					m_ParticleVector[i].MoveRect(m_ParticleVector[i].GetSpeed()); //Move particles by getting applied speed

					//Boundary check
					if (m_ParticleVector[i].GetRect()->x > 800 || m_ParticleVector[i].GetRect()->x + m_ParticleVector[i].GetRect()->w < 0 || m_ParticleVector[i].GetRect()->y + m_ParticleVector[i].GetRect()->h < 0 || m_ParticleVector[i].GetRect()->y > 600) {
						m_ParticleVector[i].SetAliveStatus(false);
					}
				}
			}
		}

		if (m_LimitedLife && m_RandomizedSpeed) {
			for (int i = 0; i < m_ParticleVector.size(); ++i) {
				if (m_ParticleVector[i].isAlive()) {
					m_ParticleVector[i].LifetimeUpdate();
				}

				if (!m_ParticleVector[i].isAlive()) {
					m_ParticleVector[i].SetAliveStatus(true);
					m_ParticleVector[i].PlaceRect(Vector2(x, y), m_ParticleWidth, m_ParticleHeight);
				}

			}
		}
	}
}

void ParticleEngine::Spawn(int ammount, int x, int y, int w, int h, bool limitedLife, int lifetime_ms) {
	srand(time(0));

	m_StartingX = x;
	m_StartingY = y;

	m_ParticleWidth = w;
	m_ParticleHeight = h;

	m_ParticleVector.resize(ammount);

	for (int i = 0; i < m_ParticleVector.size(); ++i) {
		m_ParticleVector[i].PlaceRect(Vector2(m_StartingX + rand() % 35, m_StartingY + rand() % 35), m_ParticleWidth, m_ParticleHeight);
		m_ParticleVector[i].SetLifetime(lifetime_ms + rand() % 250); //randomize lifetime 
		m_ParticleVector[i].SetAliveStatus(true);
	}

	m_Spawned = true;
	m_RandomizedSpeed = false;
	m_LimitedLife = limitedLife;
}

void ParticleEngine::Spawn(int ammount, int x, int y, int w, int h) {
	srand(time(0));

	m_StartingX = x;
	m_StartingY = y;

	m_ParticleWidth = w;
	m_ParticleHeight = h;

	m_ParticleVector.resize(ammount);

	for (int i = 0; i < m_ParticleVector.size(); ++i) {
		m_ParticleVector[i].PlaceRect(Vector2(m_StartingX + rand() % 35, m_StartingY + rand() % 35), m_ParticleWidth, m_ParticleHeight);
		m_ParticleVector[i].SetAliveStatus(true);
	}

	m_Spawned = true;
	m_RandomizedSpeed = false;
}

void ParticleEngine::ClearParticles() {
	m_ParticleVector.clear();
	m_ParticleVector.shrink_to_fit();
}
