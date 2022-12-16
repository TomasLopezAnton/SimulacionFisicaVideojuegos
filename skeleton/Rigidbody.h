#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"

class Rigidbody
{
public:
	Rigidbody(physx::PxPhysics* physics, physx::PxScene* s, Vector4 c) : scene(s), gPhysics(physics), col(c) {};

	Vector4 setColor(Vector4 c) { col = c; };

protected:
	physx::PxScene* scene;
	physx::PxPhysics* gPhysics;
	physx::PxShape* shape;
	RenderItem* renderItem;
	Vector4 col;
};