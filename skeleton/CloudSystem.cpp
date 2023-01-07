#include "CloudSystem.h"

void CloudSystem::update(double t)
{
	remainingTime -= t;

	if (remainingTime <= 0) 
	{
		Particle* seed = particleGenerators.back()->generateParticles().front();
		particleGenerators.front()->setMedianPosition(seed->getPosition());
		std::list<Particle*> l = particleGenerators.front()->generateParticles();

		for (Particle* p : l)
		{
			particles.push_back(p);

			for (ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, p);
		}

		remainingTime = frequency;

		delete seed;
	}

	ParticleSystem::update(t);
}