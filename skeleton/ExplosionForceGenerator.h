#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ExplosionForceGenerator : public ForceGenerator
{
public:

	ExplosionForceGenerator(double K, double constant, Vector3 pos, double r) : k(K), timeConstant(constant), position(pos), radius(r) {};

	virtual void updateForce(Particle* p, double t);

	void setCoefficient(double K) { k = K; };

	void setConstant(double constant) { timeConstant = constant; };

protected:
	Vector3 position;
	double k;
	double timeConstant;
	double radius;
private:
};