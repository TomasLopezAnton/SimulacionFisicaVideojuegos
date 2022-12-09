#include "ParticleContact.h"

void ParticleContact::resolve(float t)
{
	resolveVelocity(t);
	resolveInterPenetration(t);
}

void ParticleContact::resolveVelocity(float t)
{
	Vector3 initialVelocity1 = particle[0]->getVelocity();
	Vector3 initialVelocity2 = particle[1]->getVelocity();

	float inverseMass1 = particle[0]->getInvMass();
	float inverseMass2 = particle[1]->getInvMass();

	Vector3 impulse1 = -((initialVelocity1 - initialVelocity2) * (restitution + 1)) / (inverseMass1 + inverseMass2);
	Vector3 impulse2 = -impulse1;

	particle[0]->setVelocity(initialVelocity1 + inverseMass1 * impulse1);
	particle[1]->setVelocity(initialVelocity2 + inverseMass2 * impulse2);
}

void ParticleContact::resolveInterPenetration(float t)
{
	if(penetration > 0.0) 
	{
		Vector3 deltaPos1 = (particle[1]->getMass() / (particle[0]->getMass() + particle[1]->getMass())) * contactNormal;
		Vector3 deltaPos2 = (particle[0]->getMass() / (particle[1]->getMass() + particle[0]->getMass())) * contactNormal;

		particle[0]->getTransform().transform(deltaPos1);
		particle[1]->getTransform().transform(deltaPos2);
	}
}