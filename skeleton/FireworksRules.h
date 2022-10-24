#pragma once
#include "Particle.h"
#include <vector>

struct Payload
{
	unsigned type;
	unsigned count;

	Payload(unsigned t, unsigned c) : type(t), count(c) {};

	void set(unsigned t, unsigned c) { type = t; count = c; };
};

struct FireworkRule
{
	unsigned type;
	float minAge;
	float maxAge;

	Vector3 minVelocity;
	Vector3 maxVelocity;
	float damping;

	std::vector<Payload> payloads;

	void set(unsigned t, float minA, float maxA, Vector3 minVel, Vector3 maxVel, float damp, std::vector<Payload> pl) 
	{ 
		type = t;
		minAge = minA;
		maxAge = maxA;
		minVelocity = minVel;
		maxVelocity = maxVel;
		damping = damp;
		payloads = pl;
	};
};