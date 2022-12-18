#pragma once

#include <list>
#include "Rigidbody.h"
#include "RigidBodyGenerator.h"
#include "RigidbodyForceRegistry.h"
#include "RBWindForceGenerator.h"

class RigidbodySystem
{
public:
	RigidbodySystem();
	~RigidbodySystem();
	virtual void update(double t);

	RigidBodyGenerator* getRBGenerator(std::string name);
	int getRBNumber() { return bodies.size(); };

	void addRigidbody(Rigidbody* p) { bodies.push_back(p); };
	void addGenerator(RigidBodyGenerator* g) { RBGenerators.push_back(g); };
	void addForceGenerator(RBForceGenerator* g);

	void removeForceGenerator(RBForceGenerator* g);
	bool containsForceGenerator(RBForceGenerator* g);

protected:
	std::list<Rigidbody*> bodies;
	std::list<RigidBodyGenerator*> RBGenerators;
	std::list<RBForceGenerator*> forceGenerators;
	RigidbodyForceRegistry* forceRegistry;
	Vector3 bounds = { 0.0, -20, 0.0 };
private:

};