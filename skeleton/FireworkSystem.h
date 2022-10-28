#pragma once

#include "ParticleSystem.h"
#include "Firework.h"

class FireworkSystem : public ParticleSystem
{
public:
	FireworkSystem() { createFireworkRules(); gravity = { 0.0, -10.0, 0.0 }; };
	void update(double t);

	void createFireworkRules();
	void createFirework();

	ParticleGenerator* getParticleGenerator(std::string name);

protected:
	//std::list<Firework*> particles;
private:
	std::vector<FireworkRule> fireworkRules;
	int maxParticles = 1000;
};