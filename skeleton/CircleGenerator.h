#pragma once
#include "GaussianParticleGenerator.h"

class CircleGenerator : GaussianParticleGenerator
{
public:
	CircleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vDev, Vector3 pDev, int num) : GaussianParticleGenerator(n, m, p, { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }, pDev, num) 
	{
		magnitude = v.magnitude(); 
	};

	std::list<Particle*> generateParticles();
protected:
private:
	float magnitude;
};