#include "UniformParticleGenerator.h"

std::list<Particle*> UniformParticleGenerator::generateParticles()
{
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);

	std::list<Particle*> l;

	for(int i = 0; i < numParticles; i++)
	{
		Vector3 distancePos = {posWidth.x * distribution(randomGenerator), posWidth.y * distribution(randomGenerator), posWidth.z * distribution(randomGenerator)};
		Vector3 distanceVel = { velWidth.x * distribution(randomGenerator), velWidth.y * distribution(randomGenerator), velWidth.z * distribution(randomGenerator)};

		Particle* p = model->clone();
		p->setPosition(meanPos + distancePos);
		p->setVelocity(meanVel + distanceVel);
		
		l.push_back(p);
	}

	return l;
}