#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	forceRegistry = new ParticleForceRegistry();
	gravGenerator = new GravityForceGenerator(gravity);

	forceGenerators.push_back(gravGenerator);
}

ParticleSystem::~ParticleSystem()
{
	forceRegistry->clear();

	for (Particle* p : particles) delete p;
	particles.clear();

	for (ParticleGenerator* g : particleGenerators) delete g;
	particleGenerators.clear();
}

void ParticleSystem::update(double t)
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

				for(ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, p);
			}
		}
	}
	#pragma endregion

	forceRegistry->updateForces(t);

	#pragma region Update Particulas
	std::list<Particle*>::iterator it = particles.begin();

	while (it != particles.end())
	{
		(*it)->integrate(t);

		if ((*it)->getPosition().y < bounds.y || (*it)->getTime() <= 0.0)
		{
			std::list<Particle*> l = (*it)->onDeath();

			Particle* p = (*it);
			it = particles.erase(it);

			for (Particle* np : l)
			{
				particles.push_back(np);

				for (ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, np);
			}

			forceRegistry->deleteParticleRegistry(p);
			delete p;
		}

		else it++;
	}
	#pragma endregion
}