#include "GaussianParticleGenerator.h"
#include <chrono>

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
	randomGenerator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

	std::normal_distribution<double> disVelX(meanVel.x, stdDevVel.x);
	std::normal_distribution<double> disVelY(meanVel.y, stdDevVel.y);
	std::normal_distribution<double> disVelZ(meanVel.z, stdDevVel.z);

	std::normal_distribution<double> disPosX(meanPos.x, stdDevPos.x);
	std::normal_distribution<double> disPosY(meanPos.y, stdDevPos.y);
	std::normal_distribution<double> disPosZ(meanPos.z, stdDevPos.z);

	std::list<Particle*> l;

	for (int i = 0; i < numParticles; i++)
	{
		Vector3 pos = Vector3(disPosX(randomGenerator), disPosY(randomGenerator), disPosZ(randomGenerator));
		Vector3 vel = Vector3(disVelX(randomGenerator), disVelY(randomGenerator), disVelZ(randomGenerator));

		Particle* p = model->clone();
		p->setPosition(pos);
		p->setVelocity(vel);

		l.push_back(p);
	}

	return l;
}