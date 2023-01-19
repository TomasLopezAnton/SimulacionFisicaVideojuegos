#pragma once
#include "RigidbodySystem.h"
#include "StaticRigidbody.h"
#include "GaussianBodyGenerator.h"

class BoyaSystem : public RigidbodySystem
{
public:
	BoyaSystem(physx::PxPhysics* g, DinamicRigidbody* b) : gPhysics(g), boat(b)
	{
		physx::PxTransform* boyaPose = new physx::PxTransform(0, 0, 0);
		boya = new StaticRigidbody(gPhysics, b->getScene(), *boyaPose, b->getMaterial(), new physx::PxSphereGeometry(10), { 0.8, 0.7, 0.1, 1.0 }, 1e6);
		RBGenerators.push_back(new GaussianBodyGenerator("Boyas", boya, { 0, 0, 0 }, { 0, 0, 0 }, { 0.001, 0.001, 0.001 }, { 200, 0.001, 200 }, 1));
	};

	void update(double t) {};

	void repositionBoya();

	Vector3 getBoyaPosition() { return boya->getPosition(); };

	StaticRigidbody* getBoya() { return boya; };

private:
	physx::PxPhysics* gPhysics;

	DinamicRigidbody* boat;
	StaticRigidbody* boya;
};