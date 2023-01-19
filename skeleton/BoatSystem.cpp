#include "BoatSystem.h"

void BoatSystem::update(double t)
{
	RigidbodySystem::update(t);

	sail->setPosition(boat->getPosition() + boat->getRotation().rotate(sailPos));
	sail->setRotation(boat->getRotation());

	debugParticles.push_back(new Particle(boat->getPosition(), { 0, 0, 0 }, 1e6, 0.99, {0.7, 0.7, 0.1, 1.0}, 20));
}