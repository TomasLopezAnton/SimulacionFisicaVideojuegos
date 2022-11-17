#pragma once
#include "Particle.h"

class Cannonball : public Particle
{
public:
	Cannonball(Vector3 Pos, Vector3 Vel, double Mass, double Damp) : Particle(Pos, Vel, Mass, Damp, {0.1, 0.1, 0.1, 1.0}) {};
	void integrate(double t) { Particle::integrate(t); };

	Cannonball* clone() const { Cannonball* c = new Cannonball(*this); c->loadRenderItem(); return c;};

	void loadRenderItem() { Particle::loadRenderItem(); };
protected:
private:

};