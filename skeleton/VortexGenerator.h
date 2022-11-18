#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class VortexGenerator : public ForceGenerator
{
public:

	VortexGenerator(double K, Vector3 pos, double r) : k(K), position(pos), radius(r) {};

	virtual void updateForce(Particle* p, double t);

	void setCoefficients(double K) { k = K; };

protected:
	Vector3 position;
	double k;
	double radius;
private:
};