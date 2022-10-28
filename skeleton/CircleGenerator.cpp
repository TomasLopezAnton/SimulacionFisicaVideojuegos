#include "CircleGenerator.h"

std::list<Particle*> CircleGenerator::generateParticles()
{
    randomGenerator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    std::list<Particle*> l = GaussianParticleGenerator::generateParticles();

    for (Particle* p : l) p->setVelocity(p->getVelocity().getNormalized() * magnitude);

    return l;
}
