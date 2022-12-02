#pragma once
#include "ParticleSystem.h"
#include "AnchoredSpringFG.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"

class SpringParticleSystem : public ParticleSystem
{
public:
	SpringParticleSystem() {};
	~SpringParticleSystem() {};

	void update(double t);

	void generateAnchoredSpring();
	void generateDualSpring();
	void generateBungeeSpring();
	void generateBuoyantParticle();
	void clearSystem();

protected:
private:
	Particle* water = nullptr;
};