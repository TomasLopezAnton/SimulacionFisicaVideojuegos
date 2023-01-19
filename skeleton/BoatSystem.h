#pragma once

#include "RigidbodySystem.h"
#include "StaticRigidbody.h"
#include "AerodinamicForceGenerator.h"
#include "ParticleSystem.h"

class BoatSystem : public RigidbodySystem
{
public:
	BoatSystem(DinamicRigidbody* b, physx::PxPhysics* g, WindForceGenerator* wG, ParticleSystem* db) : boat(b), gPhysics(g), debugSystem(db)
	{
		scene = boat->getScene();
		addRigidbody(boat);

		physx::PxTransform* sailPose = new physx::PxTransform(boat->getPosition() + sailPos);
		sail = new StaticRigidbody(gPhysics, scene, *sailPose, boat->getMaterial(), new physx::PxBoxGeometry(0.1, 6.0, 10.0), {0.7, 0.7, 0.7, 1.0}, 10e6);
		sailRotation = sail->getRotation();

		sailFront = new Particle(boat->getPosition() + sailPos - Vector3(0.1, 0, 0), {0, 0, 0}, 1e6, 1, {0., 0., 0., 1.0}, 1e6, new physx::PxBoxGeometry(0.2, 6.0, 10));

		mast = new Particle(boat->getPosition() + mastPos, { 0, 0, 0 }, 1e6, 1, { 0.2, 0.1, 0.0, 1.0 }, 1e6, new physx::PxBoxGeometry(0.2, 8, 0.3));

		rudder = new Particle(boat->getPosition() + mastPos, { 0, 0, 0 }, 1e6, 1, { 0.2, 0.1, 0.0, 1.0 }, 1e6, new physx::PxBoxGeometry(0.2, 1, 0.3));

		addForceGenerator(new AerodinamicForceGenerator(sail, boat, wG, &rudderDirection, rudderPos));
	};

	void update(double t);

	void changeRudderDirection(int delta) 
	{ 
		Vector3 newDir = physx::PxQuat(0, 0.044 * delta, 0, 0.999).rotate(rudderDirection);
		if (abs(newDir.z) < 0.85) rudderDirection = newDir;
	};

	void rotateSail(physx::PxQuat delta)
	{		
		sailRotation = sail->getRotation() * delta;
	}

	void throwAnchor()
	{
		anchor = !anchor;
	}

private:
	DinamicRigidbody* boat;
	StaticRigidbody* sail;
	Particle* sailFront;
	Particle* rudder;
	Particle* mast;


	Vector3 mastPos = { -2.8, 6, 0 };
	Vector3 sailPos = { -3, 10, 0 };


	physx::PxQuat sailRotation;
	Vector3 rudderPos = {-0.01, -5, 0.0};
	Vector3 rudderDirection = Vector3(1, 0, 0);

	float rudderLimit = 0.6;
	float boatMaxVel = 20;

	bool anchor = true;

	physx::PxPhysics* gPhysics;
	physx::PxScene* scene;

	ParticleSystem* debugSystem;
};