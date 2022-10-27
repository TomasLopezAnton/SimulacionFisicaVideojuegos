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
	void addParticle(Particle* p) { particles.push_back(p); };

	Vector3 getGravity() { return gravity; }

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	Vector3 gravity;
	Vector3 bounds = { 300.0, 0.0, 0.0 };
private:
};