#pragma once
#include "ForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(double h, double V, double d, double g, Particle* p) : height(h), volume(V), density(d), gravity(g), particle(p) {};
	virtual void updateForce(Particle* p, double t);
protected:
	double height;
	double volume;
	double density;
	double gravity = 10.0;

	Particle* particle;
private:
};