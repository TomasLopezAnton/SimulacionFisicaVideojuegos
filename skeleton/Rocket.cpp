#include "Rocket.h"
#include <iostream>

void Rocket::integrate(double t)
{
	//std::cout << "CamDir X: " << dir.x << "Y: " << dir.y << "Z: " << dir.z << "\n";
	Vector3 dir = acc.cross(GetCamera()->getDir());
	dir.normalize();

	acc = { dir.x * jet, dir.y * jet + grav, dir.z * jet};

	std::cout << "Acceleration X: " << acc.x << " Y: " << acc.y << " Z: " << acc.z << "\n";
	Particle::integrate(t);
}