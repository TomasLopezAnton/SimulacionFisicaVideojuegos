#include "SpringForceGenerator.h"

void SpringForceGenerator::updateForce(Particle* p, double t)
{
	Vector3 force = other->getPosition() - p->getPosition();

	const float length = force.normalize();
	const float deltaX = length - restingLength;
	force *= deltaX * k;

	p->addForce(force);
}
