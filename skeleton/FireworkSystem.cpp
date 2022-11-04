#include "FireworkSystem.h"
#include <iostream>

void FireworkSystem::update(double t)
{
	ParticleSystem::update(t);
}

void FireworkSystem::createFireworkRules()
{
	fireworkRules = std::vector<FireworkRule>(9);

	#pragma region Inicializacion Reglas
	fireworkRules[0].set(0, 0, 2, { -10.0, -10.0, -10.0 }, { 10.0, 10.0, 10.0 }, 0.999, {});
	fireworkRules[1].set(1, 1, 2, { -20.0, 0.0, -20.0 }, { 20.0, 0.01, 20.0 }, 0.999, { {0, 30} });
	fireworkRules[2].set(2, 2, 3, { -30.0, 0.01, -30.0 }, { 30.0, 5.0, 30.0 }, 0.999, { {1, 5}, {0, 10} });
	fireworkRules[3].set(3, 2, 3, { -40.0, -5.0, -40.0 }, { 40.0, 30.0, 40.0 }, 0.999, { {2, 5}, {1,3}, {0,10} });
	fireworkRules[4].set(4, 0, 1, { -40.0, 30.0, 0.0 }, { -40.01, 30.01, 0.01 }, 0.999, { {2, 5}, {1,3}, {0,10}, {0, 3} });
	fireworkRules[5].set(5, 4, 5, { -10.0, 130.0, -10.0 }, { 10.0, 150.0, 10.0 }, 0.999, { {0, 30}, {1,3}, {2,2}, {3, 1}, {4, 5}});
	fireworkRules[6].set(6, 0.5, 1.5, { -10.0, -5.0, 0.0 }, { 20.0, 2.5, 0.01 }, 0.999, { {0, 10} });
	fireworkRules[7].set(7, 2, 3, { -50.0, -5.0, 0.0 }, { 50.0, 0.0, 0.01 }, 0.999, { {6, 25} });
	#pragma endregion

}

void FireworkSystem::createFirework()
{
	particles.push_back(new Firework({ 0.0, 0.0, 0.0 }, fireworkRules[5].maxVelocity, 0.999, gravity, 2.5, fireworkRules[5].payloads, 5, fireworkRules, { 1.0, 0.0, 1.0, 1.0 }));
}
