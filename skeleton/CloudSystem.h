#pragma once
#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"

class CloudSystem : public ParticleSystem
{
public:
	CloudSystem(Vector3 s, Vector3 b, float n, float f) : cloudSize(s), bounds(b), nParticles(n), frequency(f), remainingTime(f)
	{
		Particle* cloudParticle = new Particle({ 0, -1000, 0 }, { 0, 0, 0 }, 0.1, 0.7, { 0, 0, 0 }, 1000, { 0.9, 0.9, 0.9, 1.0 }, { 10, 10, 10 });
		particleGenerators.push_back(new GaussianParticleGenerator("Cloud", cloudParticle, { 0, 50, 0 }, { 0.0, 0.0, 0.0 }, { 0.001, 0.001, 0.001 }, cloudSize, n));
		particleGenerators.push_back(new UniformParticleGenerator("Seed", cloudParticle, { 0, 220, 0 }, {0, 0, 0}, {0, 0, 0}, bounds, 1));
	};

	~CloudSystem() {};

	virtual void update(double t);

protected:
	Vector3 cloudSize;
	Vector3 bounds;
	float nParticles;
	float frequency;
	float remainingTime;
private:
	std::list<std::list<Particle*>> clouds;
};
