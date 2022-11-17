#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, double Mass, double Damp, Vector3 Grv, double time, std::vector<Payload> p, int type, std::vector<FireworkRule> f, Vector4 col) : Particle(Pos, Vel, Mass, Damp, {0.0, 0.0, 0.0}, time, col)
{
	rules = f;
	payloads = p;
	fireworkType = type;
}

std::list<Particle*> Firework::onDeath()
{
	std::list<Particle*> l;

	for(Payload load : payloads)
	{
		if (load.type >= rules.size()) return l;

		#pragma region Inicializamos Particula modelo
		Colors col;

		FireworkRule rule = rules[load.type];

		Particle* p = new Firework({ 0.0, -10000000, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, rule.damping, force, 0.01, rule.payloads, rule.type, rules, col.c[rule.type]);
		#pragma endregion

		#pragma region Generamos Particulas

		Vector3 velDeviation = rule.maxVelocity - rule.minVelocity;
		velDeviation = { std::abs(velDeviation.x), std::abs(velDeviation.y), std::abs(velDeviation.z) };

		FireworkGenerator* g = new FireworkGenerator("Firework", p, pose.p, (rule.maxVelocity + rule.minVelocity) / 2,
			velDeviation, { 0.01, 0.01, 0.01 }, (rule.maxAge + rule.minAge) / 2, rule.maxAge - rule.minAge, load.count);

		std::list<Particle*> nl = g->generateParticles();

		for (Particle* np : nl) l.push_back(np);

		delete g;
		#pragma endregion

	}

	return l;
}
