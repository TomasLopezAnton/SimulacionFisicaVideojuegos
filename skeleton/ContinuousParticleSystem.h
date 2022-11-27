#pragma once
#include "ParticleSystem.h"

class ContinuousParticleSystem : public ParticleSystem
{
public:
	ContinuousParticleSystem() {};
	~ContinuousParticleSystem();
	void update(double t);

	void generateContinously(bool b) { generating = b; }
	bool getGenerating() { return generating; }

protected:
private:
	bool generating = false;
};