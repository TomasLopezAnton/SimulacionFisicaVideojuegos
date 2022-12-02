#include "SpringParticleSystem.h"

void SpringParticleSystem::update(double t)
{
	ParticleSystem::update(t);
}

void SpringParticleSystem::generateAnchoredSpring()
{
	Particle* p = new Particle({ -10.0, 20.0, 0.0 }, { 0.0, 0.0, 0.0 }, 2.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
	AnchoredSpringFG* f = new AnchoredSpringFG(1, 10, { 10.0, 20.0, 0.0 });

	particles.push_back(p);
	particles.push_back(f->getOther());

	forceRegistry->addRegistry(f, p);
	forceRegistry->addRegistry(gravGenerator, p);
}

void SpringParticleSystem::generateDualSpring()
{
	Particle* p1 = new Particle({ -10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 10.0, 0.85, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 2.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
	particles.push_back(p1);
	particles.push_back(p2);

	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);

	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);

	forceRegistry->addRegistry(f1, p1);
	forceRegistry->addRegistry(f2, p2);
	forceRegistry->addRegistry(gravGenerator, p1);
	forceRegistry->addRegistry(gravGenerator, p2);
}

void SpringParticleSystem::generateBungeeSpring()
{
	Particle* p1 = new Particle({ -10.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, 10.0, 0.85, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 10.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, 2.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
	particles.push_back(p1);
	particles.push_back(p2);

	BungeeForceGenerator* f1 = new BungeeForceGenerator(1, 10, p2);
	BungeeForceGenerator* f2 = new BungeeForceGenerator(1, 10, p1);

	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);

	forceRegistry->addRegistry(f1, p1);
	forceRegistry->addRegistry(f2, p2);
	forceRegistry->addRegistry(gravGenerator, p2);
}

void SpringParticleSystem::generateBuoyantParticle()
{
	Particle* liquid = new Particle({ 0.0, 50.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1e6, 0.99, { 0.0, 0.0, 1.0, 1.0 }, 1e6, new physx::PxBoxGeometry(10.0, 1, 10.0));
	Particle* p = new Particle({ 0.0, 52.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.8, { 1.0, 0.0, 0.0, 1.0 }, 1e6);

	particles.push_back(liquid);
	particles.push_back(p);

	BuoyancyForceGenerator* f = new BuoyancyForceGenerator(1, 20.0, 1000.0, -gravity.y, liquid);
	forceGenerators.push_back(f);

	forceRegistry->addRegistry(f, p);
	forceRegistry->addRegistry(gravGenerator, p);
}