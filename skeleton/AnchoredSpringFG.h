#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double K, double rl, Vector3 pos);
	~AnchoredSpringFG();
protected:
private:
	Vector3 position;
};