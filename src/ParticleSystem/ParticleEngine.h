#pragma once
#include "Particle.h"
#include <vector>

//This class could use some optimization
class ParticleEngine
{
public:
	ParticleEngine();
	~ParticleEngine();

	void Render();

	//\brief Updates particles; Good when trying to have particles follow an object
	//\param x - X position of said object
	//\param y - Y position of said object
	void Update(int x, int y);

	//\brief Updates particles; Needs to be called so the particles can function
	void Update();

	//\brief Spawns particles; Do NOT spawn in main loop unless you are using a keyboard/mouse button
	//\param ammount - ammount of particles to spawn
	//\param x - X position
	//\param y - Y position
	//\param w - Width of particle in pixels
	//\param h - Height of particle in pixels
	void Spawn(int ammount, int x, int y, int w, int h);

	//\brief Spawns particles; Do NOT spawn in main loop unless you are using a keyboard/mouse button
	//\param ammount - ammount of particles to spawn
	//\param x - X position
	//\param y - Y position
	//\param w - Width of particle in pixels
	//\param h - Height of particle in pixels
	//\param limitedLife - Toggle if the particles should have limited lifetime (pass true otherwise ignore)
	//\param lifetime_ms - Lifetime in milliseconds (only works if limitedLife is set to true; P.S. extra lifetime is added up to 250 ms)
	void Spawn(int ammount, int x, int y, int w, int h, bool limitedLife, int lifetime_ms);

	//Empty the vector containing the stored particles
	void ClearParticles();

private:
	std::vector<Particle> m_ParticleVector;

	bool m_Spawned;
	bool m_RandomizedSpeed;
	bool m_LimitedLife;
	
	int m_ParticleWidth;
	int m_ParticleHeight;

	int m_StartingX;
	int m_StartingY;
};

