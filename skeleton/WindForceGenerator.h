#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class WindForceGenerator : public ForceGenerator
{
public:

	WindForceGenerator(const Vector3& v, double K1, double K2, Vector3 pos, double lb, double hb) : velocity(v), k1(K1), k2(K2), position(pos), lowerBound(lb), higherBound(hb) {};

	virtual void updateForce(Particle* p, double t);

	void setVelocity(Vector3 v) { velocity = v; };

	void setCoefficients(double K1, double K2) { k1 = K1; k2 = K2; };

protected:
	Vector3 velocity;
	Vector3 position;
	double k1;
	double k2;
	double lowerBound, higherBound;
private:
};