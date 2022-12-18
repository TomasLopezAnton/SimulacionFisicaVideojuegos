#include "RigidbodySystem.h"

RigidbodySystem::RigidbodySystem()
{
	forceRegistry = new RigidbodyForceRegistry();
}

RigidbodySystem::~RigidbodySystem()
{
	forceRegistry->clear();

	for (Rigidbody* b : bodies) delete b;
	bodies.clear();

	for (RigidBodyGenerator* g : RBGenerators) delete g;
	RBGenerators.clear();

	forceGenerators.clear();
	forceRegistry->clear();
}

void RigidbodySystem::update(double t)
{
	std::list<Rigidbody*> l;

	for (RigidBodyGenerator* g : RBGenerators)
	{
		l = g->generateBodies();

		for (Rigidbody* p : l)
		{
			bodies.push_back(p);

			for (RBForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, p);
		}
	}

	std::list<Rigidbody*>::iterator it = bodies.begin();

	while (it != bodies.end())
	{
		(*it)->integrate(t);

		if ((*it)->getPosition().y < bounds.y || (*it)->getTime() <= 0.0)
		{
			std::list<Rigidbody*> l = (*it)->onDeath();

			Rigidbody* p = (*it);
			it = bodies.erase(it);

			for (Rigidbody* np : l)
			{
				bodies.push_back(np);

				for (RBForceGenerator* fg : forceGenerators) forceRegistry->addRegistry(fg, np);
			}

			forceRegistry->deleteParticleRegistry(p);
			delete p;
		}

		else it++;
	}

	forceRegistry->updateForces(t);
}

void RigidbodySystem::removeForceGenerator(RBForceGenerator* g)
{
	forceRegistry->deleteForceRegistry(g);
	forceGenerators.remove(g);
}

bool RigidbodySystem::containsForceGenerator(RBForceGenerator* g)
{
	bool found = false;
	std::list<RBForceGenerator*>::iterator it = forceGenerators.begin();

	while (!found && it != forceGenerators.end())
	{
		found = (*it) == g;
		it++;
	}

	return found;
}

void RigidbodySystem::addForceGenerator(RBForceGenerator* g)
{
	forceGenerators.push_back(g);

	for (Rigidbody* p : bodies) forceRegistry->addRegistry(g, p);
};