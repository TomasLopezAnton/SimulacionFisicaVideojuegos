#pragma once
#include "Particle.h"

class ParticleContact
{
public:
	Particle* particle[2];
	float restitution;
	float penetration;
	Vector3 contactNormal;
protected:
	void resolve(float t);
private:
	void resolveVelocity(float t);
	void resolveInterPenetration(float t);
};