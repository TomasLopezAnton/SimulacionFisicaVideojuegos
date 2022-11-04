#include "Rocket.h"
#include <iostream>

Rocket::Rocket(Vector3 Pos, Vector3 Vel, double Damp, Vector3 acc, double time) : Particle(Pos, Vel, Damp, acc, time, { 0.1, 0.1, 0.1, 1.0 })
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
}

std::list<Particle*> Rocket::onDeath()
{
	std::list<Particle*> l;

	// Particula modelo
	Particle* p = new Particle({ 0.0, -10000000, 0.0 }, { 0.0, 0.0, 0.0 }, 0.8, grav, 3, { 1.0, 0.5, 0.0, 1.0 }, 0.3);

	GaussianParticleGenerator* g = new GaussianParticleGenerator("Explosion", p, pose.p, {0, 0, 0 }, {1, 1, 1}, {0.2, 0.2, 0.2 }, 100);

	l = g->generateParticles();

	return l;
}
;
