#pragma once
#include "RBForceGenerator.h"
#include "RigidbodySystem.h"
#include "ParticleSystem.h"
#include "DinamicRigidbody.h"
#include "Particle.h"

class BuoyancyForceGeneratorRB : public RBForceGenerator
{
public:
	BuoyancyForceGeneratorRB(double h, double d, Particle* p, ParticleSystem* s) : height(h), density(d), particle(p), psystem(s) {};
	virtual void updateForce(Rigidbody* b, double t);
protected:
	double height;
	double density;

	Particle* particle;
	ParticleSystem* psystem;
private:

	Vector3 calculateForce(float h, Rigidbody* b);
};