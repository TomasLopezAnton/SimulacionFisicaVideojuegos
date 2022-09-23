#pragma once
#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping) : vel(Vel), acc(Acc), damp(damping)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.0, 0.0, 0.5, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	vel = (vel + acc * t) * pow(damp, t);
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
}