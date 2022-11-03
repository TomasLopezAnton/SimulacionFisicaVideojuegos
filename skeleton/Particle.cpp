#pragma once
#include "Particle.h"
#include <string>
#include <iostream>

Particle::Particle(Vector3 Pos, Vector3 Vel, double damping, Vector3 Acc, double time, Vector4 col, float Size) : vel(Vel), acc(Acc), damp(damping), remainingTime(time), col(col), size(Size)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, col);
}

Particle::Particle(Vector3 Pos, Vector3 Vel, double damping, Vector4 col) : vel(Vel), damp(damping), col(col)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, col);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

void Particle::integrate(double t)
{
	vel = (vel + (acc + grav) * t) * pow(damp, t);
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);

	//std::cout << vel.x << " " << vel.y << " " << vel.z << "\n";

	remainingTime -= t;
}