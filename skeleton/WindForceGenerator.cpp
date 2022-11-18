#include "WindForceGenerator.h"
#include <iostream>

void WindForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;


	if(p->getPosition().y > position.y - lowerBound && p->getPosition().y < position.y + higherBound) // El area comprendida entre los dos planos
	{
		Vector3 velDelta = velocity - p->getVelocity();

		Vector3 f = k1 * velDelta + k2 * velDelta.magnitude() * velDelta;

		p->addForce(f);
	}
}
