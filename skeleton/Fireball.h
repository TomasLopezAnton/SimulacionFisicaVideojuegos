#pragma once
#include "Particle.h"

class Fireball : public Particle
{
public:
	Fireball(Vector3 Pos, Vector3 Vel, double Damp) : Particle(Pos, Vel, Damp, { 0.7, 0.3, 0.1, 1.0 }) { acc = grv; };
	void integrate(double t) { Particle::integrate(t); };
	bool isLaser() { return false; };
protected:
	double mass = 2.0;
	Vector3 grv = { 0.0, 0.5, 0.0 };
private:

};