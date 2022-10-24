#pragma once
#include "Particle.h"

class Rocket : public Particle
{
public:
	Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc);
	void integrate(double t);

	Rocket* clone() const;

	void loadRenderItem();

protected:
	double mass = 2000.0;
	float jet = 0;
	physx::PxTransform jf_pose;
	RenderItem* jetFire;
private:
	int time = 3;
};