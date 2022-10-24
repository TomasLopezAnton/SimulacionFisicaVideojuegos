#include "ParticleSystem.h"

void ParticleSystem::update(double t)
{
	for (Particle* c : particles)
	{
		c->integrate(t);

		//if (c->getTime() <= 0)
		//{
		//	particles.remove(c);
		//	delete c;
		//}
	}
}