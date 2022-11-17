#pragma once
#include "Particle.h"

class Laser : public Particle
{
public:
	Laser(Vector3 Pos, Vector3 Vel, double Mass, double Damp) : Particle(Pos, Vel, Mass, Damp, { 1.0, 0.1, 0.1, 1.0 }) { acc = grv; };
	void integrate(double t) { Particle::integrate(t); };
	bool isLaser() { return true; };

	Laser* clone() const { Laser* l = new Laser(*this); l->loadRenderItem(); return l; };

	void loadRenderItem() { Particle::loadRenderItem(); };

protected:
	Vector3 grv = { 0.0, 0.0, 0.0 };
private:

};