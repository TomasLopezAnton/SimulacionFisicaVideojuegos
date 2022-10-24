#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem 
{
public:
	ParticleSystem() {};
	virtual void update(double t);

	ParticleGenerator* getParticleGenerator(std::string name);
	int getParticleNumber() { return particles.size(); };

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	Vector3 gravity;
	Vector3 bounds = { 300.0, 0.0, 0.0 };
private:
};