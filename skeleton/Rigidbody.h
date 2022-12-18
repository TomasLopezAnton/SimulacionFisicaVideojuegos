#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>

class Rigidbody
{
public:
	Rigidbody(physx::PxPhysics* physics, physx::PxScene* s, physx::PxGeometry* g, physx::PxMaterial* m, physx::PxTransform t, Vector4 c, double time)
		: scene(s), gPhysics(physics), geometry(g), material(m), transform(t), col(c), remainingTime(time) {};

	virtual ~Rigidbody() 
	{ 
		shape->release(); 
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}

	virtual void integrate(float t) {};

	std::list<Rigidbody*> onDeath() { return std::list<Rigidbody*>(); };

	physx::PxShape* getShape() { return shape; };

	virtual Vector3 getLinearVelocity() { return { 0, 0, 0 }; };

	virtual Vector3 getPosition() { return transform.p; };

	Vector4 getColor() { return col; };

	virtual float getInvMass() { return 0; };

	virtual bool getStatic() = 0;

	float getTime() { return remainingTime; };

	virtual void addForce(Vector3 f) {};

	Vector4 setColor(Vector4 c) { col = c; renderItem->color = col; };

	virtual void setPosition(Vector3 p) = 0;

	virtual void setVelocity(Vector3 v) {};

	virtual Rigidbody* clone() { return this; }

protected:
	physx::PxScene* scene;
	physx::PxPhysics* gPhysics;
	physx::PxShape* shape;
	physx::PxTransform transform;
	physx::PxMaterial* material;
	physx::PxGeometry* geometry;
	RenderItem* renderItem;
	Vector4 col;

	double remainingTime = 1000;

	physx::PxGeometry* extractGeometry(physx::PxGeometryHolder holder)
	{
		switch (holder.getType())
		{
		case physx::PxGeometryType::eSPHERE:
			return new physx::PxSphereGeometry(holder.sphere());
			break;
		case physx::PxGeometryType::eBOX:
			return new physx::PxBoxGeometry(holder.box());
			break;
		case physx::PxGeometryType::eCAPSULE:
			return new physx::PxCapsuleGeometry(holder.capsule());
			break;
		default:
			return new physx::PxBoxGeometry(holder.box());
			break;
		}
	}
};