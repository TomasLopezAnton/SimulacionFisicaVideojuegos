#pragma once
#include "ContinuousParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "DinamicRigidbody.h"

class FoamSystem : public ContinuousParticleSystem
{
public:
	FoamSystem(DinamicRigidbody* b, Particle* w) : boat(b), water(w)
	{
		
		Particle* foamParticle = new Particle({ 0, 0, 0 }, { 0, 0, 0 }, 0.02, 0.8, { 0, 0, 0 }, 12, { 0.7, 0.7, 0.7, 1.0 }, {0.4, 0.4, 0.4});
		
		foamGenerator = new GaussianParticleGenerator("foam", foamParticle, { 0, 0, 0 }, { 0, 0, 0 }, { 2, 0.001, 0.01 }, { 0.01, 0.001, 3 }, 10);
        particleGenerators.push_back(foamGenerator);
	};
	
	void update(double t);

protected:
private:
	DinamicRigidbody* boat;
	Particle* water;
	GaussianParticleGenerator* foamGenerator;
};