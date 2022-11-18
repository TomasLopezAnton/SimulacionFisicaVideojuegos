#include "VortexGenerator.h"
#include <iostream>

void VortexGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;


	if ((p->getPosition() - position).magnitude() < radius)
	{
		Vector3 aux = p->getPosition() - position;
		Vector3 f = k * Vector3(-aux.z, 50 - aux.y, aux.x);

		p->addForce(f);
	}
}