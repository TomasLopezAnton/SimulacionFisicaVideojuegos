#include "BuoyancyForceGeneratorRB.h"
#include <iostream>

void BuoyancyForceGeneratorRB::updateForce(Rigidbody* b, double t)
{
	if (!b->isDinamic()) return;
	
	float h = b->getPosition().y;

	physx::PxQuat bodyRotation = b->getRotation().getNormalized();
	Vector3 force;

	Vector3 positions[] = { Vector3(6, 0, 0), Vector3( -6, 0, 0.0), Vector3(0, 0, 4.0), Vector3(0, 0, -4.0) };


	for (int i = 0; i < 4; i++) 
	{
		Vector3 newPos = bodyRotation.rotate(positions[i]);
		newPos += b->getPosition();
		force = calculateForce(newPos.y, b);

		force /= 200;

		//psystem->addParticle(new Particle(newPos, { 0, 0, 0 }, 1e9, 1, { 0.0, 0.0, 0.0 }, 0.05, { 0, 1.0, 0.0, 1.0 }, { 2.0, 2.0, 2.0 }));

		b->addTorque(positions[i].cross(force));
	}

	b->addForce(calculateForce(h, b));
}

Vector3 BuoyancyForceGeneratorRB::calculateForce(float h, Rigidbody* b)
{
	double h0 = particle->getPosition().y;

	double inmersed = 0.0;
	if (h - h0 > height * 0.5) inmersed = 0.0;
	else if (h0 - h > height * 0.5)
	{
		inmersed = 1.0;
	}
	else
	{
		inmersed = (h0 - h) / height + 0.5;
	}

	return { 0.0, (float)density * (float)b->getVolume() * (float)inmersed * -b->getGravity().y, 0.0 };
}