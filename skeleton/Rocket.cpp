#include "Rocket.h"
#include <iostream>

Rocket::Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc) : Particle(Pos, Vel, Damp, acc, 1000, { 0.1, 0.1, 0.1, 1.0 })
{
	jet = acc.x; 
	grav.y = acc.y;
	jf_pose = physx::PxTransform(Pos.x - 0.5, Pos.y, Pos.z - 0.5);
	jetFire = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &jf_pose, {0.8, 0.4, 0.0, 1.0});
}

void Rocket::integrate(double t)
{
	Vector3 dir = GetCamera()->getDir();
	Vector3 a = acc;

	dir = dir - acc.getNormalized();
	dir.normalize();

	acc = Vector3(acc.x + dir.x * jet, acc.y + dir.y * jet, acc.z + dir.z * jet);

	Particle::integrate(t);

	if(time == 0)
	{
		Vector3 normalizedAcc = acc.getNormalized();
		jf_pose = physx::PxTransform(pose.p - normalizedAcc);
		time = 2;
	}

	
	/*std::cout << "Initial acceleration: " << a.x << " " << a.y << " " << a.z << "\n";
	std::cout << "Final acceleration: " << acc.x << " " << acc.y << " " << acc.z << "\n";*/

	time--;
}

Rocket* Rocket::clone() const 
{
	Rocket* r = new Rocket(*this); 
	r->loadRenderItem();
	return r;
};

void Rocket::loadRenderItem()
{ 
	Particle::loadRenderItem();
	jetFire = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &jf_pose, { 0.8, 0.4, 0.0, 1.0 }); 
};
