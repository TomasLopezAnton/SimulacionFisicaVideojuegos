#pragma once
#include "Particle.h"
#include <string>
#include <iostream>

Particle::Particle(Vector3 Pos, Vector3 Vel, double Mass, double damping, Vector3 Acc, double time, Vector4 col, float Size) : vel(Vel), acc(Acc), damp(damping), remainingTime(time), col(col), size(Size)
{
	mass = Mass;
	inverseMass = 1.0 / mass;

	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, col);


	double radius = size / 2;
	volume = (4 * 3.1415 * radius * radius * radius) / 3.0;
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double Mass, double damping, Vector4 col, double time, physx::PxGeometry* shape) : vel(Vel), damp(damping), col(col), remainingTime(time)
{
	mass = Mass;
	inverseMass = 1.0 / mass;

	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(*shape), &pose, col);

	if(shape->getType() == physx::PxGeometryType::eSPHERE) 
	{
		double radius = size / 2;
		volume = (4 * 3.1415 * radius * radius * radius) / 3.0;
	}

	if (shape->getType() == physx::PxGeometryType::eBOX) volume = size * size * size;
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double t)
{
	if (inverseMass <= 0.0) return;

	Vector3 totalAcceleration = acc;
	totalAcceleration += force * inverseMass;

	vel = (vel + totalAcceleration * t) * pow(damp, t);
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	
	remainingTime -= t;
	clearForce();
}