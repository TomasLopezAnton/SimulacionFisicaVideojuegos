#include "TimedParticleSystem.h"

void TimedParticleSystem::update(double t)
{
	currentTime -= t;

	if (currentTime <= 0)
	{
		for (ParticleGenerator* g : particleGenerators) g->generateParticles();

		currentTime = time;
	}

	ParticleSystem::update(t);
}
