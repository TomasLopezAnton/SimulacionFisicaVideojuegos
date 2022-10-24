#pragma once

#include "GaussianParticleGenerator.h"

class FireworkGenerator : public GaussianParticleGenerator
{
public:
	FireworkGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vWidth, Vector3 pWidth, float t, float tWidth, int num) : 
		GaussianParticleGenerator(n, m, p, v, vWidth, pWidth, num), particleTime(t), timeWidth(tWidth) {}

	std::list<Particle*> generateParticles();

protected:
private:
	float particleTime;
	float timeWidth;
};
