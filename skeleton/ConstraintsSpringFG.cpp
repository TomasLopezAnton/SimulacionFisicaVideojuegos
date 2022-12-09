#include "ConstraintsSpring.h"

void ConstraintsSpring::update(double t)
{
	currentLength = sFG1->getLength(particle1);

	if(currentLength < maxLength)
	{


		sFG1->updateForce(particle1, t);
		sFG2->updateForce(particle2, t);
	}
}
