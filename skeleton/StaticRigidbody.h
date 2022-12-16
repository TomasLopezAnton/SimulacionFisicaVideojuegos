#pragma once

#include "Rigidbody.h"

class StaticRigidbody : public Rigidbody
{
public:
	StaticRigidbody(physx::PxPhysics* physics, physx::PxScene* s, physx::PxTransform transform, physx::PxMaterial* material, physx::PxGeometry geometry, Vector4 c) 
		: Rigidbody(physics, s, c)
	{
		rigidbody = gPhysics->createRigidStatic(transform); 

		shape = rigidbody->createShape(geometry, *material);
		rigidbody->attachShape(*shape);

		scene->addActor(*rigidbody);

		renderItem = new RenderItem(shape, rigidbody, col);
	};

	physx::PxRigidStatic* getRigidbody() { return rigidbody; };

protected:
	physx::PxRigidStatic* rigidbody;
};