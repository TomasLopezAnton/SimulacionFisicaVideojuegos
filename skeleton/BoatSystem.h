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
		sailRotation = sail->getRotation();

		mast = new Particle(boat->getPosition() + mastPos, { 0, 0, 0 }, 1e6, 1, { 0.2, 0.1, 0.0, 1.0 }, 1e6, new physx::PxBoxGeometry(0.2, 8, 0.3));

		addForceGenerator(new AerodinamicForceGenerator(sail, boat, wG, &rudderDirection, rudderPos));
	};

	void update(double t);

	void changeRudderDirection(int delta) 
	{ 
		Vector3 newDir = physx::PxQuat(0, 0.044 * delta, 0, 0.999).rotate(rudderDirection);
		if (abs(newDir.z) < 0.6) rudderDirection = newDir;
	};

	void rotateSail(physx::PxQuat delta)
	{
		physx::PxQuat newRotation = sail->getRotation() * delta;

		float angle;
		newRotation.toRadiansAndUnitAxis(angle, physx::PxVec3(0, 1, 0));

		if(angle < 1) sailRotation = sail->getRotation() * delta;
	}

private:
	DinamicRigidbody* boat;
	StaticRigidbody* sail;
	Particle* rudder;
	Particle* mast;

	Vector3 mastPos = { -0.8, 6, 0 };

	Vector3 sailPos = { -1, 10, 0 };
	physx::PxQuat sailRotation;
	Vector3 rudderPos = {-0.1, -5, 0.0};
	Vector3 rudderDirection = Vector3(1, 0, 0);

	float rudderLimit = 0.6;

	physx::PxPhysics* gPhysics;
	physx::PxScene* scene;

	std::vector<Particle*> debugParticles;
};