#pragma once

#include "Rigidbody.h"

class StaticRigidbody : public Rigidbody
{
public:
	StaticRigidbody(physx::PxPhysics* physics, physx::PxScene* s, physx::PxTransform t, physx::PxMaterial* m, physx::PxGeometry* g, Vector4 c, double time)
		: Rigidbody(physics, s, g, m, t, c, time)
	{
		rigidbody = gPhysics->createRigidStatic(transform); 

		shape = gPhysics->createShape(*geometry, *material);
		rigidbody->attachShape(*shape);

		renderItem = new RenderItem(shape, rigidbody, col);

		scene->addActor(*rigidbody);
	};


	~StaticRigidbody()
	{
		scene->removeActor(*rigidbody);
	}

	void integrate(float t) { remainingTime -= t; };

	void setPosition(Vector3 p) { transform.p = p; rigidbody->setGlobalPose(transform); }

	physx::PxRigidStatic* getRigidbody() { return rigidbody; };

	bool getStatic() { return true; };

	virtual StaticRigidbody* clone() { return new StaticRigidbody(gPhysics, scene, transform, material, geometry, col, remainingTime); };

protected:
	physx::PxRigidStatic* rigidbody;
};