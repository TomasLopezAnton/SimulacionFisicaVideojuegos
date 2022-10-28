#pragma once
#include "CircleGenerator.h"

class FireworkGenerator : public CircleGenerator
{
public:
	FireworkGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, Vector3 vWidth, Vector3 pWidth, float t, float tWidth, int num) : 
		CircleGenerator(n, m, p, v + vWidth, vWidth, pWidth, num), particleTime(t), timeWidth(tWidth) {}

	std::list<Particle*> generateParticles();

protected:
private:
	float particleTime;
	float timeWidth;
};
