#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Grv, double time, std::vector<Payload> p, int type, Vector4 col) : Particle(Pos, Vel, Damp, {0.0, 0.0, 0.0}, 0.1, col)
{
	payloads = p;
	fireworkType = type;
}
