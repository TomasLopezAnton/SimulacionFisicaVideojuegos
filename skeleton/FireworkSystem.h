#pragma once

#include "ParticleSystem.h"
#include "Firework.h"

class FireworkSystem : public ParticleSystem
{
public:
	FireworkSystem(Vector3 pos) : position(pos) { createFireworkRules(); gravity = {0.0, -10.0, 0.0}; };
	void update(double t);

	void createFireworkRules();
	void createFirework();

	ParticleGenerator* getParticleGenerator(std::string name);

	void setPosition(Vector3 pos) { position = pos; };

protected:
private:
	Vector3 position;
	std::vector<FireworkRule> fireworkRules;
	int maxParticles = 1000;
};