#include "FireworkSystem.h"
#include <iostream>

void FireworkSystem::update(double t)
{
	ParticleSystem::update(t);

	std::list<Particle*>::iterator it = particles.begin();

	while(it != particles.end())
	{
		float distanceFromOrigin = (*it)->getPosition().magnitude();

		if ((*it)->getTime() <= 0.0 || distanceFromOrigin > bounds.x)
		{
			int type = (*it)->getType();

			if (type > 0)
			{
				std::vector<Payload> loads = fireworkRules[type].payloads;

				for (Payload l : loads) generateFirework(l.type, l.count, (*it)->getPosition());
			}

			Particle* x = (*it);
			it = particles.erase(it);

			delete x;
		}

		else it++;
	}
}

void FireworkSystem::createFireworkRules()
{
	fireworkRules = std::vector<FireworkRule>(9);

	fireworkRules[0].set(0, 0, 2, { -10.0, -10.0, -10.0 }, { 10.0, 10.0, 10.0 }, 0.999, {});
	fireworkRules[1].set(1, 1, 3, { -30.0, 0.0, -30.0 }, { 30.0, 0.01, 30.0 }, 0.999, { {0, 50} });
	fireworkRules[2].set(2, 2, 4, { -70.0, 0.01, -70.0 }, { 70.0, 5.0, 70.0 }, 0.999, { {1, 5}, {0, 50} });
	fireworkRules[3].set(3, 2, 4, { -50.0, -20.0, -50.0 }, { 50.0, 30.0, 50.0 }, 0.999, { {2, 5}, {1,3}, {0,50} });
	fireworkRules[4].set(4, 0, 2, { -50.0, 30.0, 0.0 }, { -50.01, 30.01, 0.01 }, 0.999, { {2, 5}, {1,3}, {0,50}, {0, 3} });
	fireworkRules[5].set(5, 2, 4, { -10.0, 90.0, -10.0 }, { 10.0, 100.0, 10.0 }, 0.999, { {0, 50}, {1,3}, {2,2}, {3, 1}, {4, 5}});
	fireworkRules[6].set(6, 0.5, 1.5, { -30.0, -5.0, 0.0 }, { 30.0, 2.5, 0.01 }, 0.999, { {0, 50} });
	fireworkRules[7].set(7, 2, 4, { -50.0, -5.0, 0.0 }, { 50.0, 0.0, 0.01 }, 0.999, { {6, 25} });
}

void FireworkSystem::generateFirework(unsigned type, unsigned count, const Vector3 pos)
{
	if (type >= fireworkRules.size()) return;

	Colors col;

	FireworkRule rule = fireworkRules[type];

	Particle* p = new Firework({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, rule.damping, gravity, 0.01, rule.payloads, rule.type, col.c[type]);
	p->setGravity(gravity);

	Vector3 velDeviation = rule.maxVelocity - rule.minVelocity;
	velDeviation = { std::abs(velDeviation.x), std::abs(velDeviation.y), std::abs(velDeviation.z) };

	FireworkGenerator* g = new FireworkGenerator(std::to_string(particleGenerators.size()), p, pos, (rule.maxVelocity + rule.minVelocity) / 2,
		velDeviation, { 0.01, 0.01, 0.01 }, (rule.maxAge + rule.minAge) / 2, rule.maxAge - rule.minAge, count);
	
	//particleGenerators.push_back(g);

	std::list<Particle*> l = g->generateParticles();
	
	delete g;

	for (Particle* np : l) particles.push_back(np);
}
