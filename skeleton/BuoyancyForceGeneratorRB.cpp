#include "BuoyancyForceGeneratorRB.h"
#include <iostream>

void BuoyancyForceGeneratorRB::updateForce(Rigidbody* b, double t)
{
	if (!b->isDinamic()) return;
	
	float h = b->getPosition().y;

	physx::PxQuat bodyRotation = b->getRotation().getNormalized();
	Vector3 force;

	Vector3 positions[] = { Vector3(8, h - 0.01, 0), Vector3( -8, h, 0 ), Vector3(0, h, 4), Vector3(0, h, -4)};


	for (int i = 0; i < 4; i++) 
	{
		positions[i] = bodyRotation.rotate(positions[i]);
		force = calculateForce(positions[i].y, b);
		std::cout << force.y << " | ";
		if (force.y != 0.0)
		{
			bool t;
		}

		force /= 8000000;

		//psystem->addParticle(new Particle(positions[i], { 0, 0, 0 }, 1e9, 1, { 0.0, 0.0, 0.0 }, 0.05, { 0, 1.0, 0.0, 1.0 }, { 2.0, 2.0, 2.0 }));

		//b->addTorque(force.y * positions[i]);
	}

	std::cout << "\n";

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