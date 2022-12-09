#pragma once
#include "Particle.h"

class ParticleContact
{
public:
	ParticleContact(Particle* p1, Particle* p2) { particle[0] = p1; particle[1] = p2; }
	void resolve(float t);

	void setPenetration(float p) { penetration = p; };

	void setNormal(Vector3 n) { contactNormal = n; };

protected:
private:
	Particle* particle[2];
	float restitution = 1.0;
	float penetration;
	Vector3 contactNormal;

	void resolveVelocity(float t);
	void resolveInterPenetration(float t);
};