#include "ParticleSystem.h"

void ParticleSystem::update(double t)
{
	if (generating)
	{
		std::list<Particle*> l;
		for (ParticleGenerator* g : particleGenerators)
		{
			l = g->generateParticles();
			for (Particle* p : l) particles.push_back(p);
		}
	}

	std::list<Particle*>::iterator it = particles.begin();

	while (it != particles.end())
	{
		(*it)->integrate(t);

		if ((*it)->getPosition().y < bounds.y) particles.erase(it);

		else it++;
	}
}
