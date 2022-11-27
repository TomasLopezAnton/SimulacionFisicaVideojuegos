#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"

class ParticleSystem 
{
public:
	ParticleSystem();
	~ParticleSystem();
	virtual void update(double t);

	ParticleGenerator* getParticleGenerator(std::string name);
	int getParticleNumber() { return particles.size(); };

	void addParticle(Particle* p) { particles.push_back(p); forceRegistry->addRegistry(gravGenerator, p); };
	void addGenerator(ParticleGenerator* g) { particleGenerators.push_back(g); };
	void addForceGenerator(ForceGenerator* g);

	void removeForceGenerator(ForceGenerator* g);

	Vector3 getGravity() { return gravity; }

	bool containsForceGenerator(ForceGenerator* g);

	void setGravity(Vector3 g) { gravity = g; gravGenerator->setGravity(g); }

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	std::list<ForceGenerator*> forceGenerators;
	ParticleForceRegistry* forceRegistry;
	GravityForceGenerator* gravGenerator;
	Vector3 gravity = {0.0, -10.0, 0.0};
	Vector3 bounds = { 0.0, -0.01, 0.0 };
private:

};