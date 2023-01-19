#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vWidth, Vector3 pWidth, int num);
	std::list<Particle*> generateParticles();

	void setPWidth(Vector3 p) { posWidth = p; };

protected:
	Vector3 velWidth;
	Vector3 posWidth;
	std::uniform_real_distribution<float> distribution;
private:

};
