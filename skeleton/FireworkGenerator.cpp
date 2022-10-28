#include "FireworkGenerator.h"

std::list<Particle*> FireworkGenerator::generateParticles()
{
    std::default_random_engine randomGenerator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    std::list<Particle*> l = CircleGenerator::generateParticles();

    std::normal_distribution<float> timeDis(particleTime, timeWidth);

    for(Particle* p : l) 
    {
        float t = timeDis(randomGenerator);
        p->setTime(t);
    }

    return l;
}
