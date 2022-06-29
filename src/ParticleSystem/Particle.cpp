#include "Particle.h"
#include "../TimerModule.h"

Particle::Particle() {
	m_ParticleLifetime = 0;
	m_StartingLifetime = 0;
	m_Alive = false;
}

void Particle::LifetimeUpdate() {
	float life_decrement = TimerModule::GetDelta() * 1000.0f;
	
	m_ParticleLifetime -= life_decrement;

	if (m_ParticleLifetime <= 0) {
		m_Alive = false;
		m_ParticleLifetime = m_StartingLifetime; //reset lifetime
	}
}

void Particle::SetLifetime(float ms) {
	m_ParticleLifetime = ms;
	m_StartingLifetime = m_ParticleLifetime;
}

void Particle::SetAliveStatus(bool status) {
	m_Alive = status;
}

float Particle::GetLifetime() {
	return m_ParticleLifetime;
}

bool Particle::isAlive() {
	return m_Alive;
}