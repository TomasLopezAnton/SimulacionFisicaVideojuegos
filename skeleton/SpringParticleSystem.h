#pragma once
#include "ParticleSystem.h"
#include "AnchoredSpringFG.h"
#include "BungeeForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "ConstraintsSpring.h"
#include "ConstraintsRope.h"
#include <iostream>
#include "Colors.h"
#include "ParticleContact.h"

class SpringParticleSystem : public ParticleSystem
{
public:
	SpringParticleSystem() { floor = new Particle({ 0.0, -100.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1e6, 0.01, { 0.2, 0.2, 0.2, 1.0 }, 1e6, new physx::PxBoxGeometry(1000.0, 10.0, 1000.0), { 1000.0, 10.0, 1000.0 });};
	~SpringParticleSystem() {};

	void update(double t);

	void generateAnchoredSpring();
	void generateDualSpring();
	void generateConstraintsSpring();
	void generateBungeeSpring();
	void generateSlinky();
	void generateConstraintsSlinky();
	void generateBuoyantParticle();
	void generateRope();
	void clearSystem();

	void velRedParticle(Vector3 vel) { if (redParticle != nullptr) redParticle->setVelocity(redParticle->getVelocity() + vel); };
	void stopRedParticle() { if (redParticle != nullptr) redParticle->setVelocity({0, 0, 0}); };

protected:
private:
	Particle* water = nullptr;
	Particle* floor = nullptr;
	Particle* redParticle = nullptr;
	std::list<ConstraintsSpring*> constraints;
	std::list<ConstraintsRope*> constraintsr;
	std::list<ParticleContact*> contacts;
};