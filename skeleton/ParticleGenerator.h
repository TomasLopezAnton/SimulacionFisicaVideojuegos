#pragma once

#include <list>
#include <random>
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, int num);
	void setParticle(Particle* m) { model = m; };
	virtual std::list<Particle*> generateParticles() = 0;

	void setMedianPosition(Vector3 mp) { meanPos = mp; };
	void setMedianVelocity(Vector3 mv) { meanVel = mv; };
	void setParticleNumber(int n) { numParticles = n; };

protected:
	std::string name;
	Vector3 meanPos, meanVel;
	double generationProbability = 1;
	int numParticles;
	Particle* model;
	std::default_random_engine randomGenerator;
private:
};