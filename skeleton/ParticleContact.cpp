#include "ParticleContact.h"

void ParticleContact::resolve(float t)
{
	resolveVelocity(t);
	resolveInterPenetration(t);
}

void ParticleContact::resolveVelocity(float t)
{
	Vector3 initialVelocity1 = particle[1]->getVelocity();
	Vector3 initialVelocity2 = particle[2]->getVelocity();

	float inverseMass1 = particle[1]->getInvMass();
	float inverseMass2 = particle[2]->getInvMass();

	Vector3 impulse1 = -((initialVelocity1 - initialVelocity2) * (restitution + 1)) / (inverseMass1 + inverseMass2);
	Vector3 impulse2 = -impulse1;

	particle[1]->setVelocity(initialVelocity1 + inverseMass1 * impulse1);
	particle[2]->setVelocity(initialVelocity2 + inverseMass2 * impulse2);
}