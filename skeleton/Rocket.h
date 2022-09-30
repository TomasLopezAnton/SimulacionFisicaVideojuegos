#pragma once
#include "Particle.h"

class Rocket : public Particle
{
public:
	Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc) : Particle(Pos, Vel, Damp, acc, { 0.1, 0.1, 0.1, 1.0 }) { jet = acc.x; };
	void integrate(double t);

	bool isLaser() { return false; };
protected:
	double mass = 2000.0;
	float jet = 0;
	float grav = -0.0;
private:

};