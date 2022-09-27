#pragma once
#include "Particle.h"

class Laser : public Particle
{
public:
	Laser(Vector3 Pos, Vector3 Vel, double Damp) : Particle(Pos, Vel, Damp, { 1.0, 0.1, 0.1, 1.0 }) { acc = grv; };
	//void integrate(double t);
	bool isLaser() { return true; };
protected:
	double mass = 0.1;
	Vector3 grv = { 0.0, 0.0, 0.0 };
private:

};