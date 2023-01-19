#include "FoamSystem.h"

void FoamSystem::update(double t)
{
	//particleGenerators.front()->setMedianPosition({ boat->getPosition().x, 0, boat->getPosition().y });
	particleGenerators.front()->setParticleNumber(min(boat->getLinearVelocity().magnitude() / 5, 4));

	Vector3 pos = boat->getRotation().rotate({ -11, 0, 0 }) + boat->getPosition();
	
	particleGenerators.front()->setPWidth(boat->getRotation().rotate(foamGenerator->getStdDevPos()));
	particleGenerators.front()->setMedianPosition({ pos.x, water->getPosition().y + (float)3.4, pos.z});
	particleGenerators.front()->setMedianVelocity({ -boat->getLinearVelocity().x / 2, min(boat->getLinearVelocity().magnitude() * 2, 10), -boat->getLinearVelocity().z / 2 });
	ContinuousParticleSystem::update(t);
}