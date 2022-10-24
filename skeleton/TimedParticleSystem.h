#pragma once

#include "ParticleSystem.h"

class TimedParticleSystem : public ParticleSystem
{
public:
	TimedParticleSystem(float time) : ParticleSystem(), time(time), currentTime(time) {};
	void update(double t);

protected:
private:
	float time = 0;
	float currentTime = 0;
};