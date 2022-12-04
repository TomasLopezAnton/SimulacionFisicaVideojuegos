#pragma once
#include "ForceGenerator.h"
#include "ParticleSystem.h"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(double h, double V, double d, Particle* p, ParticleSystem* ps) : height(h), volume(V), density(d), particle(p), particleSystem(ps) {};
	virtual void updateForce(Particle* p, double t);
protected:
	double height;
	double volume;
	double density;

	Particle* particle;
private:
	ParticleSystem* particleSystem;
};