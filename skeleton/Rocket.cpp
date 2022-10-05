#include "Rocket.h"
#include <iostream>

void Rocket::integrate(double t)
{
	Vector3 dir = GetCamera()->getDir();
	dir = dir - acc.getNormalized();
	dir.normalize();

	acc = {acc.x + dir.x * jet, acc.y + dir.y * jet + grav, acc.z + dir.z * jet};

	std::cout << "Acceleration X: " << acc.x << " Y: " << acc.y << " Z: " << acc.z << "\n";
	Particle::integrate(t);
}