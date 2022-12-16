#pragma once

#include "Rigidbody.h"

class DinamicRigidbody : public Rigidbody
{
public:

	DinamicRigidbody(physx::PxPhysics* physics, physx::PxScene* s, physx::PxTransform transform, physx::PxMaterial* material, physx::PxGeometry geometry, Vector4 c)
		: Rigidbody(physics, s, c)
	{ 
		rigidbody = gPhysics->createRigidDynamic(transform); 

		shape = rigidbody->createShape(geometry, *material);
		rigidbody->attachShape(*shape);

		scene->addActor(*rigidbody);

		renderItem = new RenderItem(shape, rigidbody, col);
	};

	physx::PxRigidDynamic* getRigidbody() { return rigidbody; };

protected:
	physx::PxRigidDynamic* rigidbody;
};