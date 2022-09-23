#pragma once
#include "Particle.h"

class Cannonball : public Particle
{
public:
	Cannonball(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damp) : Particle(Pos, Vel, grv, Damp) { acc = grv; };
	void integrate(double t);
protected:
	double mass = 200.0;
	Vector3 grv = { 0.0, -0.48, 0.0 };
private:

};