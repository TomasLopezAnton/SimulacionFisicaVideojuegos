#include "ConstraintsSpring.h"
#include <iostream>

void ConstraintsSpring::update(double t)
{
	currentLength = sFG1->getLength(particle1);

	if(currentLength < maxLength)
	{
		float pen = (particle1->getSize().x + particle2->getSize().x) - currentLength;

		if (currentLength < minLength || pen > 0.0)
		{
			contact->setPenetration(pen);
			contact->setNormal((particle2->getPosition() - particle1->getPosition()).getNormalized());
			contact->resolve(t);
		}

		//if(pen > 0.0)
		//{

		//}

		sFG1->updateForce(particle1, t);
		sFG2->updateForce(particle2, t);

	}
}
