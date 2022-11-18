#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
public:

	GravityForceGenerator(const Vector3& g) : gravity(g) {};

	virtual void updateForce(Particle* p, double t);

	void setGravity(Vector3 g) { gravity = g; };

protected:
	Vector3 gravity;
private:
};