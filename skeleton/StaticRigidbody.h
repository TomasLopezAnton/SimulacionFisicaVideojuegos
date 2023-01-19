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

	virtual bool isDinamic() { return false; };

	void setPosition(Vector3 p) { transform.p = p; rigidbody->setGlobalPose(transform); }

	void setRotation(physx::PxQuat r) { physx::PxTransform t = rigidbody->getGlobalPose(); t.q = r; rigidbody->setGlobalPose(t); };

	physx::PxRigidStatic* getRigidbody() { return rigidbody; };

	Vector3 getPosition() { return rigidbody->getGlobalPose().p; };

	virtual physx::PxQuat getRotation() { return rigidbody->getGlobalPose().q; };

	bool getStatic() { return true; };

	virtual StaticRigidbody* clone() { return new StaticRigidbody(gPhysics, scene, transform, material, geometry, col, remainingTime); };

protected:
	physx::PxRigidStatic* rigidbody;
};