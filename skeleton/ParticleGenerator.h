#pragma once

#include <list>
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, int num) : name(n), model(m), meanPos(p), meanVel(v), numParticles(num) {};
	void setParticle(Particle* m) { model = m; };
	virtual std::list<Particle*> generateParticles() = 0;

protected:
	std::string name;
	Vector3 meanPos, meanVel;
	double generationProbability = 1;
	int numParticles;
	Particle* model;
private:
};