#pragma once
#include "RigidBodyGenerator.h"

class GaussianBodyGenerator : public RigidBodyGenerator
{
public:
	GaussianBodyGenerator(std::string n, Rigidbody* m, Vector3 p, Vector3 v, Vector3 vDev, Vector3 pDev, int num) : RigidBodyGenerator(n, m, p, v, num), stdDevVel(vDev), stdDevPos(pDev) {}
	std::list<Rigidbody*> generateBodies();

	void setPositionDeviation(Vector3 pd) { stdDevPos = pd; };
	void setVelocityDeviation(Vector3 vd) { stdDevVel = vd; };

protected:
	Vector3 stdDevVel;
	Vector3 stdDevPos;
private:
};