#pragma once
#include "Particle.h"

class Cannonball : public Particle
{
public:
	Cannonball(Vector3 Pos, Vector3 Vel, double Damp) : Particle(Pos, Vel, Damp, {0.1, 0.1, 0.1, 1.0}) { acc = grv; };
	void integrate(double t) { Particle::integrate(t); };
	//std::string getID();
	bool isLaser() { return false; };
protected:
	double mass = 20000.0;
	Vector3 grv = { 0.0, -0.48, 0.0 };
private:

};