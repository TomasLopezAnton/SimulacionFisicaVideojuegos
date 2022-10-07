#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
	//UniformParticleGenerator(Vector3 vWidth, Vector3 pWidth) : ParticleGenerator(), velWidth(vWidth), posWidth(pWidth) {}
protected:
	Vector3 velWidth;
	Vector3 posWidth;
private:
};
