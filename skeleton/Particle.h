#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Acc, double time = 1000, Vector4 col = {1.0, 1.0, 1.0, 1.0});
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector4 col = {1.0, 1.0, 1.0, 1.0});
	~Particle();

	virtual void integrate(double t);


	virtual bool isLaser() { return false; };

	virtual Particle* clone() const { return new Particle(*this); };

	void setAcceleration(Vector3 a) { acc = a; };

	void setVelocity(Vector3 v) { vel = v; };

	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); }

protected:
	Vector3 vel;
	Vector3 acc = {0.0, 0.0, 0.0};
	double damp;
	physx::PxTransform pose; // Pasar la direccion de la pose a RenderItem para que se actualice automaticamente 
	RenderItem* renderItem;
	double remainingTime;
private:
	
};