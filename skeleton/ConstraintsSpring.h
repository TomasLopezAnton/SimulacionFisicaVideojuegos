#pragma once
#include "SpringForceGenerator.h"
#include "ParticleContact.h"

class ConstraintsSpring
{
public:
	ConstraintsSpring(double K, double rl, double maxL, double minL, Particle* p1, Particle* p2) : maxLength(maxL), minLength(minL), particle1(p1), particle2(p2)
	{
		contact = new ParticleContact(particle1, particle2);
		sFG1 = new SpringForceGenerator(K, rl, p2);
		sFG2 = new SpringForceGenerator(K, rl, p1);
	};

	~ConstraintsSpring() {};

	virtual void update(double t);

protected:
	double maxLength;
	double minLength;
	double currentLength;
private:
	Particle* particle1;
	Particle* particle2;
	ParticleContact* contact;
	SpringForceGenerator* sFG1;
	SpringForceGenerator* sFG2;
};