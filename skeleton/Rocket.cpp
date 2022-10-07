#include "Rocket.h"
#include <iostream>

Rocket::Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc) : Particle(Pos, Vel, Damp, acc, { 0.1, 0.1, 0.1, 1.0 })
{
	jet = acc.x; 
	grav = acc.y;
	jf_pose = physx::PxTransform(Pos.x - 0.5, Pos.y, Pos.z - 0.5);
	jetFire = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &jf_pose, {0.8, 0.4, 0.0, 1.0});
}

void Rocket::integrate(double t)
{
	Vector3 dir = GetCamera()->getDir();
	dir = dir - acc.getNormalized();
	dir.normalize();

	acc = {acc.x + dir.x * jet, acc.y + dir.y * jet + grav, acc.z + dir.z * jet};

	Particle::integrate(t);

	if(time == 0)
	{
		Vector3 normalizedAcc = acc.getNormalized();
		jf_pose = physx::PxTransform(pose.p - normalizedAcc);
		time = 2;
	}

	time--;
}