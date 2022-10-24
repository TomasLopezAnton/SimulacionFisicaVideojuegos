#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vWidth, Vector3 pWidth, int num) : ParticleGenerator(n, m, p, v, num), velWidth(vWidth), posWidth(pWidth) 
{
	distribution = std::uniform_real_distribution<float>(-1.0, 1.0);
}

std::list<Particle*> UniformParticleGenerator::generateParticles()
{
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