#pragma once

#include "ParticleGenerator.h"
#include <random>

class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vWidth, Vector3 pWidth, int num) : ParticleGenerator(n, m, p, v, num), velWidth(vWidth), posWidth(pWidth) {}
	std::list<Particle*> generateParticles();
protected:
	Vector3 velWidth;
	Vector3 posWidth;
private:
	std::default_random_engine randomGenerator;
};
