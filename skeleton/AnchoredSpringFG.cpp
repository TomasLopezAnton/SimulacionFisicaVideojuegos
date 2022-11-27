#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double K, double rl, Vector3 pos) : SpringForceGenerator(K, rl, nullptr)
{
	position = pos;
	other = new Particle(position, { 0.0, 0.0, 0.0 }, 1e6, 0.0, { 1.0, 0.0, 0.0, 1.0 }, 1e6, new physx::PxBoxGeometry(2.0, 2.0, 2.0));
}