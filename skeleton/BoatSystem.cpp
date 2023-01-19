#include "BoatSystem.h"

void BoatSystem::update(double t)
{
	RigidbodySystem::update(t);
	
	physx::PxQuat boatRot = boat->getRotation();

	sail->setPosition(boat->getPosition() + boatRot.rotate(sailPos));

	sail->setRotation(sailRotation /** boatRot*/);

	mast->setPosition(boat->getPosition() + boatRot.rotate(mastPos));

	Vector3 normalVector = { 1, 0, 0 };
	normalVector = sail->getRotation().rotate(normalVector).getNormalized() * 20;
	
	//debugParticles.push_back(new Particle(boat->getPosition() + normalVector, { 0, 0, 0 }, 1e9, 1, { 1.0, 0.0, 0.0 }, 0.05, { 1.0, 0.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }));
	//debugParticles.push_back(new Particle(boat->getPosition() + boat->getRotation().rotate(rudderDirection) * 20, {0, 0, 0}, 1e9, 1, {1.0, 0.0, 0.0}, 0.05, {1.0, 0.0, 1.0, 1.0}, {0.5, 0.5, 0.5}));
	

	//Vector3 r = Vector3(0, 0, 1).cross(rudderDirection);
	//physx::PxQuat rudderRotation = {}
	//rudder->setRotation(boat->getRotation() *  )

	//std::cout << rudderDirection.x << " " << rudderDirection.y << " " << rudderDirection.z << "\n";

	//debugParticles.push_back(new Particle(boat->getPosition(), { 0, 0, 0 }, 1e6, 0.99, {0.7, 0.7, 0.1, 1.0}, 20));

	std::cout << boat->getLinearVelocity().magnitude() << "\n";
}