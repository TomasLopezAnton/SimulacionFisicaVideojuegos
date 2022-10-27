#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector3 Acc, double time = 1000, Vector4 col = {0.2, 0.4, 1.0, 1.0});
	Particle(Vector3 Pos, Vector3 Vel, double Damp, Vector4 col = {1.0, 1.0, 1.0, 1.0});
	~Particle();

	virtual void integrate(double t);

	virtual Particle* clone() const { Particle* r = new Particle(*this); r->loadRenderItem(); return r;};

	virtual void loadRenderItem() { renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, col); };

	void setAcceleration(Vector3 a) { acc = a; };

	void setVelocity(Vector3 v) { vel = v; };

	void setGravity(Vector3 g) { grav = g; };

	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); };

	void setTime(int t) { remainingTime = t; };

	//void setColor(Vector4 c) { col = c; renderItem->color. };

	Vector3 getVelocity() { return vel; };

	Vector3 getPosition() { return pose.p; };

	double getTime() { return remainingTime; };

	virtual int getType() { return -1; };

protected:
	Vector3 vel;
	Vector3 acc = {0.0, 0.0, 0.0};
	Vector3 grav = {0.0, 0.0, 0.0};
	Vector4 col;
	double damp;
	physx::PxTransform pose; // Pasar la direccion de la pose a RenderItem para que se actualice automaticamente 
	RenderItem* renderItem;
	double remainingTime;
private:
	
};