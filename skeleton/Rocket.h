#pragma once
#include "Particle.h"

class Rocket : public Particle
{
public:
	Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc);
	void integrate(double t);

	bool isLaser() { return false; };

	Particle* clone() { return new Rocket(*this); };
protected:
	double mass = 2000.0;
	float jet = 0;
	float grav = -0.0;
	physx::PxTransform jf_pose;
	RenderItem* jetFire;
private:
	int time = 3;
};