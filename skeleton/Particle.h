#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Acc, Vector4 col = {1.0, 1.0, 1.0, 1.0});
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector4 col = {1.0, 1.0, 1.0, 1.0});
	~Particle();

	virtual void integrate(double t);

	void setAcceleration(Vector3 a) { acc = a; };

	virtual bool isLaser() { return false; };

protected:
	Vector3 vel;
	Vector3 acc = {0.0, 0.0, 0.0};
	double damp;
	physx::PxTransform pose; // Pasar la direccion de la pose a RenderItem para que se actualice automaticamente 
	RenderItem* renderItem;
private:
	
};