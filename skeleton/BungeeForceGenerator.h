#pragma once
#include "SpringParticleSystem.h"

class BungeeForceGenerator : public SpringForceGenerator
{
public:
	BungeeForceGenerator(double K, double rl, Particle* o) : SpringForceGenerator(K, rl, o) {};

	void updateForce(Particle* p, double t);

protected:
private:
};