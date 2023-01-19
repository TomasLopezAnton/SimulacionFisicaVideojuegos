#include "BoyaSystem.h"

void BoyaSystem::repositionBoya()
{
	RBGenerators.front()->setMedianPosition({ boat->getPosition().x, 0,  boat->getPosition().y });
	Rigidbody* newBoya = RBGenerators.front()->generateBodies().front();

	boya->setPosition(newBoya->getPosition());

	delete newBoya;
}