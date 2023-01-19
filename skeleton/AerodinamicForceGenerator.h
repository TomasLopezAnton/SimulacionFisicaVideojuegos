#pragma once
#include "RBForceGenerator.h"
#include "WindForceGenerator.h"
#include "StaticRigidbody.h"

class AerodinamicForceGenerator : public RBForceGenerator
{
public:
	AerodinamicForceGenerator(StaticRigidbody* s, DinamicRigidbody* b, WindForceGenerator* wFG, Vector3* rd, Vector3 rp) : sail(s), boat(b), wind(wFG), rudderDirection(rd), rudderPosition(rp)
	{
		dimensions = sail->getDimensions();
	}

	void updateForce(Rigidbody* p, double duration);

protected:
	Vector3 dimensions;
	Vector3	position;
	Vector3 windVel;
	physx::PxQuat orientation;

	Vector3* rudderDirection;
	Vector3 rudderPosition;

	float airDensity = 1.225;

	StaticRigidbody* sail;
	DinamicRigidbody* boat;
	WindForceGenerator* wind;
};