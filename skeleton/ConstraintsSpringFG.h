#pragma once
#include "SpringForceGenerator.h"

class ConstraintsSpringFG : public SpringForceGenerator
{
public:
	ConstraintsSpringFG(double K, double rl, double maxL, double minL, Particle* o) : maxLength(maxL), minLength(minL), SpringForceGenerator(K, rl, o) {};
	~ConstraintsSpringFG() {};

	virtual void updateForce(Particle* p, double t);

protected:
	double maxLength;
	double minLength;
private:
};

//if (deltaX > 0) std::cout << deltaX << "\n";