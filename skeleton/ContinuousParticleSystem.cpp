#include "ContinuousParticleSystem.h"

void ContinuousParticleSystem::update(double t)
{
#pragma region Generacion Continua
	if (generating)
	{
		std::list<Particle*> l;
		for (ParticleGenerator* g : particleGenerators)
		{
			l = g->generateParticles();
			for (Particle* p : l)
			{
				particles.push_back(p);

				for (ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, p);
			}
		}
	}
#pragma endregion

	ParticleSystem::update(t);
}