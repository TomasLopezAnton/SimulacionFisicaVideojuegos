#pragma once

#include "DinamicRigidbody.h"
#include <list>
#include <random>

class RBForceGenerator
{
public:
	virtual void updateForce(Rigidbody* p, double duration) = 0;
protected:
	std::string name;
	double t = -1;
private:
};