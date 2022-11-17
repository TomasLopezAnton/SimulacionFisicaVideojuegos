#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"

class ParticleSystem 
{
public:
	ParticleSystem() { forceRegistry = new ParticleForceRegistry(); gravGenerator = new GravityForceGenerator(gravity); };
	~ParticleSystem();
	virtual void update(double t);

	ParticleGenerator* getParticleGenerator(std::string name);
	int getParticleNumber() { return particles.size(); };

	void addParticle(Particle* p) { particles.push_back(p); forceRegistry->addRegistry(gravGenerator, p);
	};
	void addGenerator(ParticleGenerator* g) { particleGenerators.push_back(g); };

	void generateContinously(bool b) { generating = b; }

	Vector3 getGravity() { return gravity; }
	bool getGenerating() { return generating; }

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	ParticleForceRegistry* forceRegistry;
	GravityForceGenerator* gravGenerator;
	Vector3 gravity = {0.0, -10.0, 0.0};
	Vector3 bounds = { 0.0, -0.01, 0.0 };
private:
	bool generating = false;
};