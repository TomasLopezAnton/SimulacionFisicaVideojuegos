#include "FireworkSystem.h"
#include <iostream>

void FireworkSystem::update(double t)
{
	ParticleSystem::update(t);

	//std::list<Particle*>::iterator it = particles.begin();

	//while(it != particles.end())
	//{
	//	if ((*it)->getTime() <= 0.0)
	//	{
	//		if(Firework* x = dynamic_cast<Firework*>((*it)))
	//		{
	//			std::list<Particle*> l = x->onDeath();

	//			Particle* p = (*it);
	//			it = particles.erase(it);

	//			for (Particle* np : l) particles.push_back(np);

	//			delete p;
	//		}
	//	}

	//	else it++;
	//}
}

void FireworkSystem::createFireworkRules()
{
	fireworkRules = std::vector<FireworkRule>(9);

	fireworkRules[0].set(0, 0, 2, { -10.0, -10.0, -10.0 }, { 10.0, 10.0, 10.0 }, 0.999, {});
	fireworkRules[1].set(1, 1, 3, { -30.0, 0.0, -30.0 }, { 30.0, 0.01, 30.0 }, 0.999, { {0, 50} });
	fireworkRules[2].set(2, 2, 4, { -40.0, 0.01, -40.0 }, { 40.0, 5.0, 40.0 }, 0.999, { {1, 5}, {0, 50} });
	fireworkRules[3].set(3, 2, 4, { -50.0, -20.0, -50.0 }, { 50.0, 30.0, 50.0 }, 0.999, { {2, 5}, {1,3}, {0,50} });
	fireworkRules[4].set(4, 0, 2, { -50.0, 30.0, 0.0 }, { -50.01, 30.01, 0.01 }, 0.999, { {2, 5}, {1,3}, {0,50}, {0, 3} });
	fireworkRules[5].set(5, 2, 4, { -10.0, 90.0, -10.0 }, { 10.0, 100.0, 10.0 }, 0.999, { {0, 50}, {1,3}, {2,2}, {3, 1}, {4, 5}});
	fireworkRules[6].set(6, 0.5, 1.5, { -30.0, -5.0, 0.0 }, { 30.0, 2.5, 0.01 }, 0.999, { {0, 50} });
	fireworkRules[7].set(7, 2, 4, { -50.0, -5.0, 0.0 }, { 50.0, 0.0, 0.01 }, 0.999, { {6, 25} });
}

void FireworkSystem::createFirework()
{
	particles.push_back(new Firework({ 0.0, 0.0, 0.0 }, fireworkRules[5].maxVelocity, 0.999, gravity, 2.5, fireworkRules[5].payloads, 5, fireworkRules, { 1.0, 0.0, 1.0, 1.0 }));
}
