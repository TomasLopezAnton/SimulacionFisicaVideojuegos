#pragma once
#include "Particle.h"

class Fireball : public Particle
{
public:
	Fireball(Vector3 Pos, Vector3 Vel, double Damp) : Particle(Pos, Vel, Damp, { 0.7, 0.3, 0.1, 1.0 }) {};
	void integrate(double t) { Particle::integrate(t); };

	Fireball* clone() const { Fireball* f = new Fireball(*this);  f->loadRenderItem(); return f; };

	void loadRenderItem() { Particle::loadRenderItem(); };

protected:
	double mass = 2.0;
private:

};