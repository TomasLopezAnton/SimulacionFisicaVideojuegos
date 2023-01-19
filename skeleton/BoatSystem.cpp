#include "BoatSystem.h"

void BoatSystem::update(double t)
{
	RigidbodySystem::update(t);
	
	if (anchor) boat->setVelocity({ 0, 0, 0 });

	else if (boat->getLinearVelocity().magnitude() > boatMaxVel) boat->setVelocity(boat->getLinearVelocity().getNormalized() * boatMaxVel);

	physx::PxQuat boatRot = boat->getRotation();

	sail->setPosition(boat->getPosition() + boatRot.rotate(sailPos));
	sail->setRotation(sailRotation /** boatRot*/);

	sailFront->setPosition(boat->getPosition() + boatRot.rotate(sailPos - Vector3(1, 0, 0)));
	sailFront->setRotation(sailRotation /** boatRot*/);

	mast->setPosition(boat->getPosition() + boatRot.rotate(mastPos));

	//Indicadores de direccion
	Vector3 normalVector = { -1, 0, 0 };
	normalVector = sail->getRotation().rotate(normalVector).getNormalized() * 20;

	Vector3 r = boat->getPosition() + boat->getRotation().rotate(Vector3(rudderDirection.x, rudderDirection.y, rudderDirection.z).getNormalized() * 10);

	debugSystem->addParticle(new Particle(boat->getPosition() + normalVector, { 0, 0, 0 }, 1e9, 1, { 1.0, 0.0, 0.0 }, 0.05, { 1.0, 0.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }));
	debugSystem->addParticle(new Particle({ r.x, 10, r.z }, { 0, 0, 0 }, 0.1, 0.05, { 0.7, 0.7, 0.1, 1.0 }, 0.05));
}