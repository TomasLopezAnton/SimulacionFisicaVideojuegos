#include "BungeeForceGenerator.h"
#include <iostream>

void BungeeForceGenerator::updateForce(Particle* p, double t)
{
	Vector3 force = p->getPosition() - other->getPosition();

	float length = force.normalize();

	length = length - restingLength;
	
	if (length < 0.0) return;

	else
	{
		force *= -(length * k);
		p->addForce(force);
	}
}
