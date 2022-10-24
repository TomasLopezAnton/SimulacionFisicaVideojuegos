#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(std::string n, Particle* m, Vector3 p, Vector3 v, int num) : name(n), model(m), meanPos(p), meanVel(v), numParticles(num)
{
};