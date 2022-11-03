#pragma once
#include "Particle.h"
#include "FireworksRules.h"
#include "FireworkGenerator.h"
#include "Colors.h"
#include <random>

class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Grv, double time, std::vector<Payload> p, int type, std::vector<FireworkRule> f, Vector4 col);
	~Firework();

	void integrate(double t) { Particle::integrate(t); };
	std::vector<Payload> explode() { return payloads; };

	std::list<Particle*> onDeath();

	Firework* clone() const { Firework* fw = new Firework(*this); fw->loadRenderItem(); return fw; };

	void loadRenderItem() { Particle::loadRenderItem(); };
protected:
	double mass = 0.1;
private:
	unsigned fireworkType;
	std::vector<Payload> payloads;
	std::vector<FireworkRule> rules;
};