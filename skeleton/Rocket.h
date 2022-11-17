#pragma once
#include "Particle.h"
#include "GaussianParticleGenerator.h"

class Rocket : public Particle
{
public:
	Rocket(Vector3 Pos, Vector3 Vel, double Mass, double Damp, Vector3 acc, double time);
	void integrate(double t);

	Rocket* clone() const;

	void loadRenderItem();

	std::list<Particle*> onDeath();

protected:
	float jet = 0;
	physx::PxTransform jf_pose;
	RenderItem* jetFire;
private:
	int time = 3;
};