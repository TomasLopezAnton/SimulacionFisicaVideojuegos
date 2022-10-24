#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
public:
	GaussianParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vDev, Vector3 pDev, int num) : ParticleGenerator(n, m, p, v, num), stdDevVel(vDev), stdDevPos(pDev) {}
	std::list<Particle*> generateParticles();

	void setPositionDeviation(Vector3 pd) { stdDevPos = pd; };
	void setVelocityDeviation(Vector3 vd) { stdDevVel = vd; };

protected:
	Vector3 stdDevVel;
	Vector3 stdDevPos;
private:

};