#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration) 
	{
		for(auto it = begin(); it != end(); it++)
		{
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) { insert(FRPair(fg, p)); };

	void deleteParticleRegistry(Particle* p) 
	{
		auto it = begin();
		bool found = false;

		while(!found && it != end())
		{
			if (it->second == p)
			{
				it = erase(it);
				found = true;
			}

			else it++;
		}
	};
};