#pragma once
#include "Particle.h"
#include "FireworksRules.h"
#include <random>

class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Grv, double time, std::vector<Payload> p, int type, Vector4 col);

	void integrate(double t) { Particle::integrate(t); };
	std::vector<Payload> explode() { return payloads; };

	int getType() { return fireworkType; }

	Firework* clone() const { Firework* fw = new Firework(*this); fw->loadRenderItem(); return fw; };

	void loadRenderItem() { Particle::loadRenderItem(); };
protected:
	double mass = 0.1;
private:
	unsigned fireworkType;
	std::vector<Payload> payloads;
};