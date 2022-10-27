#pragma once
#include "Particle.h"
#include <list>

class ReproducingParticle : public Particle 
{
public:
	ReproducingParticle(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Acc, double time = 1000, Vector4 col = { 0.2, 0.4, 1.0, 1.0 }) : Particle(Pos, Vel, Damp, Acc, time, col) {};

	virtual ReproducingParticle* clone() const override { ReproducingParticle* r = new ReproducingParticle(*this); r->loadRenderItem(); return r; };

	virtual std::list<Particle*> onDeath() { return std::list<Particle*>(); };
protected:
private:
};