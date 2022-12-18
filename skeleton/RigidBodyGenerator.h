#pragma once

#include <list>
#include <random>
#include <chrono>
#include "Rigidbody.h"

class RigidBodyGenerator
{
public:
	RigidBodyGenerator(std::string n, Rigidbody* m, Vector3 p, Vector3 v, int num) : name(n), model(m), meanPos(p), meanVel(v), numBodies(num){};
	~RigidBodyGenerator() { delete model; }
	void setModel(Rigidbody* m) { model = m; };
	virtual std::list<Rigidbody*> generateBodies() = 0;

	void setMedianPosition(Vector3 mp) { meanPos = mp; };
	void setMedianVelocity(Vector3 mv) { meanVel = mv; };
	void setBodyNumber(int n) { numBodies = n; };

protected:
	std::string name;
	Vector3 meanPos, meanVel;
	double generationProbability = 1;
	int numBodies;
	Rigidbody* model;
	std::default_random_engine randomGenerator;
	bool isStatic;
private:
};