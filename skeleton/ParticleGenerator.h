#pragma once

#include <list>
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(std::string n, Particle* m) : name(n), model(m) {};
	void setParticle(Particle* model) {};
	virtual std::list<Particle*> generateParticles() = 0;

protected:
	std::string name;
	Vector3 meanPos, meanVel;
	double generationProbability;
	int numParticles = 0;
	Particle* model;
private:
};