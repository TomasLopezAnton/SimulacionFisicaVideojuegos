#include "ExplosionForceGenerator.h"
#include <numbers>

void ExplosionForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10) return;

	Vector3 aux = p->getPosition() - position;
	double r = sqrt((aux.x * aux.x + aux.y * aux.y + aux.z * aux.z));

	if(r < radius)
	{
		Vector3 f = (k / (r * r)) * aux * exp(-t / timeConstant);
		p->addForce(f);
	}
}