#pragma once

#include <map>
#include "RBForceGenerator.h"
#include <iostream>

typedef std::pair<RBForceGenerator*, Rigidbody*> RBFRPair;

class RigidbodyForceRegistry : public std::multimap<RBForceGenerator*, Rigidbody*>
{
public:
	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); it++)
		{
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(RBForceGenerator* fg, Rigidbody* p) { insert(RBFRPair(fg, p)); };

	void deleteParticleRegistry(Rigidbody* p)
	{
		auto it = begin();

		while (it != end())
		{
			if (it->second == p)
			{
				it = erase(it);
			}

			else it++;
		}
	};

	void deleteForceRegistry(RBForceGenerator* g) { erase(g); };
};