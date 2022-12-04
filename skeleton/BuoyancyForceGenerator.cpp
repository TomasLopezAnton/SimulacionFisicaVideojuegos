#include "BuoyancyForceGenerator.h"
#include <iostream>

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	double h = p->getPosition().y;
	double h0 = particle->getPosition().y;

	double inmersed = 0.0;
	if (h - h0 > height * 0.5) inmersed = 0.0;
	else if (h0 - h > height * 0.5) inmersed = 1.0;
	else inmersed = (h0 - h) / height + 0.5;

	Vector3 force = { 0.0, (float)density * (float)p->getVolume() * (float)inmersed * -particleSystem->getGravity().y, 0.0};

	p->addForce(force);
}