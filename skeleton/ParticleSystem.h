#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem 
{
public:
	ParticleSystem() {};
	~ParticleSystem();
	virtual void update(double t);

	ParticleGenerator* getParticleGenerator(std::string name);
	int getParticleNumber() { return particles.size(); };

	void addParticle(Particle* p) { particles.push_back(p); };
	void addGenerator(ParticleGenerator* g) { particleGenerators.push_back(g); };

	void generateContinously(bool b) { generating = b; }

	Vector3 getGravity() { return gravity; }
	bool getGenerating() { return generating; }

protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	Vector3 gravity;
	Vector3 bounds = { 0.0, -0.01, 0.0 };
private:
	bool generating = false;
};