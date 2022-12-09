#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double K, double rl, Particle* o) : k(K), restingLength(rl), other(o) {}
	~SpringForceGenerator() {};

	virtual void updateForce(Particle* p, double t);

	inline void setK(double K) { k = K; };

	Particle* getOther() { return other; };

	double getLength(Particle* p) { return (other->getPosition() - p->getPosition()).normalize(); };

protected:
	double k;
	double restingLength;
	Particle* other;
private:
};