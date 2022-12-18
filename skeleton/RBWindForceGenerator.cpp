#include "RBWindForceGenerator.h"
#include <iostream>

void RBWindForceGenerator::updateForce(Rigidbody* p, double t)
{
	if (p->getStatic()) return;

	//std::cout << p->getPosition().y << "\n";

	if (p->getPosition().y > position.y - lowerBound && p->getPosition().y < position.y + higherBound) // El area comprendida entre los dos planos
	{
		Vector3 velDelta = velocity - p->getLinearVelocity();

		Vector3 f = k1 * velDelta + k2 * velDelta.magnitude() * velDelta;

		p->addForce(f);

		//std::cout << "Force: " << f.x << " " << f.y << " " << f.z << "\n";
	}
}
