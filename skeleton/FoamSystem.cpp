#include "FoamSystem.h"

void FoamSystem::update(double t)
{

	//particleGenerators.front()->setMedianPosition({ boat->getPosition().x, 0, boat->getPosition().y });
	particleGenerators.front()->setParticleNumber(min(boat->getLinearVelocity().magnitude() / 5, 2));

	Vector3 dir = boat->getRotation().rotate({ 1, 0, 0 }).getNormalized();
	Vector3 pos = boat->getRotation().rotate({ -8, 0, 0 }) + boat->getPosition();
	
	particleGenerators.front()->setPWidth(boat->getRotation().rotate(foamGenerator->getStdDevPos()));
	particleGenerators.front()->setMedianPosition({ pos.x, water->getPosition().y + (float)3.3, pos.z});
	particleGenerators.front()->setMedianVelocity({ - boat->getLinearVelocity().x / 3 * - dir.x, 0, -boat->getLinearVelocity().z / 3 * - dir.z});
	ContinuousParticleSystem::update(t);
}