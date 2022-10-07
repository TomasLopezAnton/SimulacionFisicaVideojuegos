#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem 
{
public:
	ParticleSystem() {};
	void update() {};

	ParticleGenerator* getParticleGenerator(std::string name);

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
private:
};