#include "GravityForceGenerator.h"
#include <iostream>

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	if(fabs(p->getInvMass()) < 1e-5) return;

	Vector3 f = gravity * p->getMass();
	p->addForce(f);
}
