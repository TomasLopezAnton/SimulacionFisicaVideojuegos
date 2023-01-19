#pragma once

#include "RigidbodySystem.h"
#include "StaticRigidbody.h"
#include "AerodinamicForceGenerator.h"

class BoatSystem : public RigidbodySystem
{
public:
	BoatSystem(DinamicRigidbody* b, physx::PxPhysics* g, WindForceGenerator* wG) : boat(b), gPhysics(g)
	{
		scene = boat->getScene();
		addRigidbody(boat);

		physx::PxTransform* sailPose = new physx::PxTransform(boat->getPosition() + sailPos);
		sail = new StaticRigidbody(gPhysics, scene, *sailPose, boat->getMaterial(), new physx::PxBoxGeometry(0.1, 6.0, 10.0), {0.7, 0.7, 0.7, 1.0}, 10e6);

		addForceGenerator(new AerodinamicForceGenerator(sail, boat, wG, rudderDirection, rudderPos));
	};

	void update(double t);

private:
	DinamicRigidbody* boat;
	StaticRigidbody* sail;

	Vector3 sailPos = { 1, 10, 0 };
	Vector3 rudderPos = {0, -5, 0};
	Vector3* rudderDirection = new Vector3(0.2, 0, 0.8);

	physx::PxPhysics* gPhysics;
	physx::PxScene* scene;

	std::vector<Particle*> debugParticles;
};