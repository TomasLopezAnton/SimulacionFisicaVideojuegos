#pragma once
#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "DinamicRigidbody.h"

class CloudSystem : public ParticleSystem
{
public:
	CloudSystem(DinamicRigidbody* target, Vector3 s, Vector3 b, float nP, int nC, float f) : boat(target), cloudSize(s), bounds(b), nParticles(nP), maxClouds(nC), frequency(f)
	{
		Particle* cloudParticle = new Particle({ 0, -1000, 0 }, { 0, 0, 0 }, 0.1, 0.9, { 0, 0, 0 }, 1000, { 0.9, 0.9, 0.9, 1.0 }, { 15, 15, 15 });
		Particle* cloudParticle2 = new Particle({ 0, -1000, 0 }, { 0, 0, 0 }, 0.1, 0.9, { 0, 0, 0 }, 1000, { 0.9, 0.9, 0.9, 1.0 }, { 15, 15, 15 });
		particleGenerators.push_back(new GaussianParticleGenerator("Cloud", cloudParticle, { 0, 0, 0 }, { 0.0, 0.0, 0.0 }, { 0.001, 0.001, 0.001 }, cloudSize, 1));
		particleGenerators.push_back(new UniformParticleGenerator("Seed", cloudParticle2, { 0, 220, 0 }, {0, 0, 0}, {0, 0, 0}, bounds, 1));

		for (int i = 0; i < maxClouds; i++)
		{
			generatedParticles.push_back(0);
			seedDeltas.push_back({ 0, 0, 0 });
		}
	};

	~CloudSystem() 
	{
		clouds.clear();
	};

	virtual void update(double t);

	void generateCloudParticle(int index, std::list<Particle*>* cloud);

	void moveCloudParticle(int index, std::list<Particle*>* cloud);

protected:
	Vector3 cloudSize;
	Vector3 bounds;
	DinamicRigidbody* boat;
	float nParticles;
	int maxClouds;
    int nClouds = 0;
	float remainingTime = 0;
	float frequency;
private:
	std::list<std::list<Particle*>*> clouds;
	std::vector<int> generatedParticles;
	std::vector<Vector3> seedDeltas;
};
