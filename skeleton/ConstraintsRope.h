#pragma once
#include "ParticleContact.h"
#include "SpringForceGenerator.h"
#include <iostream>

class ConstraintsRope
{
public:
	ConstraintsRope(double K, double maxL, Particle* p1, Particle* p2) : maxLength(maxL), particle1(p1), particle2(p2)
	{
		contact = new ParticleContact(particle1, particle2);
		sFG1 = new SpringForceGenerator(K, maxL / 2, p2);
		sFG2 = new SpringForceGenerator(K, maxL / 2, p1);
	};

	~ConstraintsRope() {};

	virtual void update(double t) 
	{
		currentLength = (particle1->getPosition() - particle2->getPosition()).normalize();

		if(currentLength > maxLength)
		{
			sFG1->updateForce(particle1, t);
			sFG2->updateForce(particle2, t);
		}
	}

protected:
	double maxLength;
	double currentLength;
private:
	Particle* particle1;
	Particle* particle2;
	ParticleContact* contact;
	SpringForceGenerator* sFG1;
	SpringForceGenerator* sFG2;
};