#pragma once
#include "ParticleSystem.h"
#include "AnchoredSpringFG.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "ConstraintsSpring.h"

class SpringParticleSystem : public ParticleSystem
{
public:
	SpringParticleSystem() {};
	~SpringParticleSystem() {};

	void update(double t);

	void generateAnchoredSpring();
	void generateDualSpring();
	void generateConstraintsSpring();
	void generateBungeeSpring();
	void generateSlinky();
	void generateConstraintsSlinky();
	void generateBuoyantParticle();
	void clearSystem();

protected:
private:
	Particle* water = nullptr;
	std::list<ConstraintsSpring*> constraints;
};