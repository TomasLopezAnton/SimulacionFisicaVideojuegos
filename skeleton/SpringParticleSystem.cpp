#include "SpringParticleSystem.h"


void SpringParticleSystem::update(double t)
{
	for (ParticleContact* c : contacts)  
	{
		Particle* p = c->getParticle(1);
		float pen = (floor->getSize().y + p->getSize().x - abs(floor->getPosition().y - p->getPosition().y));


		if (pen > 0.0)
		{
			c->setPenetration(pen);
			c->setNormal({0.0, 1.0, 0.0});
			c->setRestitution(1.0);
			c->resolve(t);
		}
	}

	for (ConstraintsSpring* c : constraints) c->update(t);

	for (ConstraintsRope* c : constraintsr) c->update(t);

	ParticleSystem::update(t);

	if(redParticle != nullptr)
	{
		Vector3 p = redParticle->getPosition();

		redParticle->setPosition({ p.x, 10.0f, p.z });
	}
}

void SpringParticleSystem::generateAnchoredSpring()
{
	Particle* p = new Particle({ -10.0, 50.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
	AnchoredSpringFG* f = new AnchoredSpringFG(1, 10, { 10.0, 50.0, 0.0 });

	particles.push_back(p);
	particles.push_back(f->getOther());

	forceRegistry->addRegistry(f, p);
	forceRegistry->addRegistry(gravGenerator, p);
}

void SpringParticleSystem::generateDualSpring()
{
	Particle* p1 = new Particle({ -10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
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

void SpringParticleSystem::generateConstraintsSpring()
{
	Particle* p1 = new Particle({ -10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, { 0.0, 0.0, 1.0, 1.0 });
	particles.push_back(p1);
	particles.push_back(p2);

	constraints.push_back(new ConstraintsSpring(1, 10, 25, 10, p1, p2));

	forceRegistry->addRegistry(gravGenerator, p1);
	forceRegistry->addRegistry(gravGenerator, p2);
}

void SpringParticleSystem::generateSlinky()
{
	Particle* p1 = new Particle({ 0.0, 60.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 0.0, 55.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 1.0, 0.5, 0.0, 1.0 });
	Particle* p3 = new Particle({ 0.0, 50.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 1.0, 1.0, 0.0, 1.0 });
	Particle* p4 = new Particle({ 0.0, 45.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 0.0, 1.0, 0.0, 1.0 });
	Particle* p5 = new Particle({ 0.0, 43.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 0.0, 0.0, 1.0, 1.0 });

	particles.push_back(p1);
	particles.push_back(p2);
	particles.push_back(p3);
	particles.push_back(p4);
	particles.push_back(p5);

	SpringForceGenerator* f1 = new SpringForceGenerator(0.5, 5, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(0.5, 5, p3);
	SpringForceGenerator* f3 = new SpringForceGenerator(0.5, 5, p4);
	SpringForceGenerator* f4 = new SpringForceGenerator(0.5, 5, p5);

	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);
	forceGenerators.push_back(f3);
	forceGenerators.push_back(f4);

	forceRegistry->addRegistry(f1, p1);
	forceRegistry->addRegistry(f2, p2);
	forceRegistry->addRegistry(f3, p3);
	forceRegistry->addRegistry(f4, p4);
	forceRegistry->addRegistry(gravGenerator, p1);
	forceRegistry->addRegistry(gravGenerator, p2);
	forceRegistry->addRegistry(gravGenerator, p3);
	forceRegistry->addRegistry(gravGenerator, p4);
	forceRegistry->addRegistry(gravGenerator, p5);
}

void SpringParticleSystem::generateConstraintsSlinky()
{
	Particle* p1 = new Particle({ 50.0, 240.0, 50.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, { 1.0, 0.0, 0.0, 1.0 });
	particles.push_back(p1);
	forceRegistry->addRegistry(gravGenerator, p1);
	ParticleContact* c = new ParticleContact(floor, p1);
	contacts.push_back(c);
	Particle* previousP = p1;

	for(int i = 1; i <= 11; i++)
	{
		Colors col = Colors();
		
		Particle* p = new Particle({ 0.0, (float)(240.0 - 20 * i), 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.6, col.rainbow[i % col.rainbow.size()]);
		particles.push_back(p);
		constraints.push_back(new ConstraintsSpring(1, 5, 3000, 2, p, previousP));
		forceRegistry->addRegistry(gravGenerator, p);
		previousP = p;
		ParticleContact* c = new ParticleContact(floor, p);
		contacts.push_back(c);
	}
}

void SpringParticleSystem::generateBungeeSpring()
{
	Particle* p1 = new Particle({ -15.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.4, { 1.0, 0.0, 0.0, 1.0 });
	Particle* p2 = new Particle({ 15.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.4, { 0.0, 0.0, 1.0, 1.0 });
	particles.push_back(p1);
	particles.push_back(p2);

	BungeeForceGenerator* f1 = new BungeeForceGenerator(0.5, 10, p2);
	BungeeForceGenerator* f2 = new BungeeForceGenerator(0.5, 10, p1);

	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);

	forceRegistry->addRegistry(f1, p1);
	forceRegistry->addRegistry(f2, p2);
	forceRegistry->addRegistry(gravGenerator, p2);
}

void SpringParticleSystem::generateBuoyantParticle()
{
	if (water == nullptr)
	{
		water = new Particle({ 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1e6, 0.99, { 0.0, 0.0, 1.0, 1.0 }, 1e6, new physx::PxBoxGeometry(100.0, 1, 100.0));
		particles.push_back(water);
	}

	Particle* p = new Particle({ 0.0, 4.0, 0.0 }, { 0.0, 0.0, 0.0 }, 10.0, 0.6, { 1.0, 0.0, 0.0, 1.0 }, 1e6, new physx::PxSphereGeometry(2.0), {2.0, 2.0, 2.0});

	particles.push_back(p);

	BuoyancyForceGenerator* f = new BuoyancyForceGenerator(1, 2.0, 1000.0, water, this);
	forceGenerators.push_back(f);

	forceRegistry->addRegistry(f, p);
	forceRegistry->addRegistry(gravGenerator, p);
}

void SpringParticleSystem::generateRope()
{
	Colors col = Colors();

	Particle* p1 = new Particle({ -10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[RED]);
	Particle* p2 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[BLUE]);
	Particle* p3 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[GREEN]);
	Particle* p4 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[YELLOW]);
	Particle* p5 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[ORANGE]);
	Particle* p6 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[PINK]);
	Particle* p7 = new Particle({ 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.85, col.c[PURPLE]);
	particles.push_back(p1);
	particles.push_back(p2);
	particles.push_back(p3);
	particles.push_back(p4);
	particles.push_back(p5);
	particles.push_back(p6);
	particles.push_back(p7);

	redParticle = p1;

	constraintsr.push_back(new ConstraintsRope(0.2, 10, p1, p2));
	constraintsr.push_back(new ConstraintsRope(0.2, 10, p2, p3));
	constraintsr.push_back(new ConstraintsRope(0.2, 10, p3, p4));
	constraintsr.push_back(new ConstraintsRope(0.2, 10, p4, p5));
	constraintsr.push_back(new ConstraintsRope(0.2, 10, p5, p6));
	constraintsr.push_back(new ConstraintsRope(0.2, 10, p6, p7));

	//forceRegistry->addRegistry(gravGenerator, p1);
	forceRegistry->addRegistry(gravGenerator, p2);
	forceRegistry->addRegistry(gravGenerator, p3);
	forceRegistry->addRegistry(gravGenerator, p4);
	forceRegistry->addRegistry(gravGenerator, p5);
	forceRegistry->addRegistry(gravGenerator, p6);
	forceRegistry->addRegistry(gravGenerator, p7);
}

void SpringParticleSystem::clearSystem()
{
	forceRegistry->clear();

	for (Particle* p : particles) delete p;
	particles.clear();

	for (ParticleGenerator* g : particleGenerators) delete g;
	particleGenerators.clear();

	for (ConstraintsSpring* c : constraints) delete c;
	constraints.clear();

	for (ConstraintsRope* c : constraintsr) delete c;
	constraintsr.clear();


	forceGenerators.clear();
	forceRegistry->clear();

	water = nullptr;
	redParticle = nullptr;
}