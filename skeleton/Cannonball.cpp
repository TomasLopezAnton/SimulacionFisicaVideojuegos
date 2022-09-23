#include "Cannonball.h"

void Cannonball::integrate(double t)
{
	vel = (vel + acc * t) * pow(damp, t);
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
}