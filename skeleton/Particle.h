#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damp);
	~Particle();

	virtual void integrate(double t);

protected:
	Vector3 vel;
	Vector3 acc;
	double damp;
	physx::PxTransform pose; // Pasar la direccion de la pose a RenderItem para que se actualice automaticamente 
	RenderItem* renderItem;
private:
	
};