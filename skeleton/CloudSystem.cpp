#include "CloudSystem.h"
#include <iostream>

void CloudSystem::update(double t)
{
	if(remainingTime <= 0 && nClouds < maxClouds)
	{
		Particle* seed = particleGenerators.back()->generateParticles().front();

		particles.push_back(seed);
		for (ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, seed);

		std::list<Particle*>* cloud = new std::list<Particle*>();

		cloud->emplace_front(seed);
		clouds.push_back(cloud);

		nClouds++;
		remainingTime = frequency;
	}

	int i = 0;

	for(std::list<Particle*>* cloud : clouds)
	{
		particleGenerators.back()->setMedianPosition({ boat->getPosition().x, 220,  boat->getPosition().z });
		
		Particle* seed = cloud->front();

		if(seed->getPosition().x > boat->getPosition().x + bounds.x || seed->getPosition().x < boat->getPosition().x - bounds.x 
			|| seed->getPosition().z > boat->getPosition().z + bounds.z || seed->getPosition().z < boat->getPosition().z - bounds.z ) // Si la nube est� fuera de los bounds
		{
			Particle* newSeed = particleGenerators.back()->generateParticles().front();

			seedDeltas.at(i) = newSeed->getPosition() - seed->getPosition();

			seed->setPosition(newSeed->getPosition());

			delete newSeed;

			std::list<Particle*>::iterator it = cloud->begin();
			it++;

			while(it != cloud->end()) 
			{
				(*it)->setVelocity({ 0, 0, 0 });
				(*it)->clearForce();
				it++;
			}

			generatedParticles.at(i) = 0;
		}

		if(generatedParticles.at(i) != nParticles)
		{
			if (cloud->size() <= nParticles) generateCloudParticle(i, cloud);

			else moveCloudParticle(i, cloud);
		}

		i++;
	}

	ParticleSystem::update(t);

	remainingTime -= t;
}

void CloudSystem::generateCloudParticle(int index, std::list<Particle*>* cloud)
{
	Particle* seed = cloud->front();

	particleGenerators.front()->setMedianPosition(seed->getPosition());
	Particle* p = particleGenerators.front()->generateParticles().front();
	p->setVelocity(seed->getVelocity());
	particles.push_back(p);

	for (ForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, p);

	cloud->push_back(p);

	generatedParticles.at(index)++;
}

void CloudSystem::moveCloudParticle(int index, std::list<Particle*>* cloud)
{

	Particle* seed = cloud->front();

	std::list<Particle*>::iterator it = cloud->begin();

	for (int i = 0; i < generatedParticles.at(index) + 1; i++) it++;

	(*it)->setPosition(((*it)->getPosition() + seedDeltas.at(index)));

	generatedParticles.at(index)++;
}