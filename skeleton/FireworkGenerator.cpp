#include "FireworkGenerator.h"

std::list<Particle*> FireworkGenerator::generateParticles()
{
    std::list<Particle*> l = GaussianParticleGenerator::generateParticles();

    std::normal_distribution<float> timeDis(particleTime, timeWidth);

    for(Particle* p : l) 
    {
        float t = timeDis(randomGenerator);
        p->setTime(t);
    }

    return l;
}
