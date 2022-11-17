#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator 
{
public:
	virtual void updateForce(Particle* p, double duration) = 0;
protected:
	std::string name;
	double t = -1;
private:
};