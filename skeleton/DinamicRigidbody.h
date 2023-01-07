#pragma once

#include "Rigidbody.h"

class DinamicRigidbody : public Rigidbody
{
public:

	DinamicRigidbody(physx::PxPhysics* physics, physx::PxScene* s, physx::PxTransform t, physx::PxMaterial* m, physx::PxGeometry* g, Vector4 c, double time)
		: Rigidbody(physics, s, g, m, t, c, time)
	{ 
		rigidbody = gPhysics->createRigidDynamic(transform); 

		shape = gPhysics->createShape(*geometry, *material);
		rigidbody->attachShape(*shape);

		renderItem = new RenderItem(shape, rigidbody, col);

		scene->addActor(*rigidbody);
	};

	~DinamicRigidbody()
	{
		scene->removeActor(*rigidbody);
	}

	virtual DinamicRigidbody* clone()
	{
		physx::PxTransform tr = physx::PxTransform(transform.p);

		physx::PxGeometry* g = extractGeometry(shape->getGeometry());

		return new DinamicRigidbody(gPhysics, scene, transform, material, g, col, remainingTime);
	};

	void integrate(float t) override { rigidbody->clearForce(); rigidbody->clearTorque(); remainingTime -= t; };

	virtual bool isDinamic() { return true; };

	void rotate(physx::PxQuat r) { physx::PxTransform t = rigidbody->getGlobalPose(); t.q *= r; rigidbody->setGlobalPose(t); };

	void setPosition(Vector3 p) { transform.p = p; rigidbody->setGlobalPose(transform); }

	void setVelocity(Vector3 v) { rigidbody->setLinearVelocity(v); };

	void setMass(float m) { return rigidbody->setMass(m); };

	void addForce(Vector3 f) { rigidbody->addForce(f); };

	void addTorque(Vector3 t) { rigidbody->addTorque(t); };

	physx::PxRigidDynamic* getRigidbody() { return rigidbody; };

	virtual Vector3 getLinearVelocity() { return rigidbody->getLinearVelocity(); };

	float getInvMass() { return 1.0 / rigidbody->getMass(); };

	float getMass() { return rigidbody->getMass(); }

	Vector3 getPosition() { return rigidbody->getGlobalPose().p; };

	virtual physx::PxQuat getRotation() { return rigidbody->getGlobalPose().q; };

	bool getStatic() { return false; };

protected:
	physx::PxRigidDynamic* rigidbody;
};