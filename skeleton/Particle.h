#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>
#include <list>
#include <iostream>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, double Mass, double Damp, Vector3 Acc, double time = 1000, Vector4 col = {0.2, 0.4, 1.0, 1.0}, float Size = 1.0);
	Particle(Vector3 Pos, Vector3 Vel, double Mass, double Damp, Vector4 col = {1.0, 1.0, 1.0, 1.0}, double time = 1000, physx::PxGeometry* shape = new physx::PxSphereGeometry(1.0));
	~Particle();

	virtual void integrate(double t);

	virtual Particle* clone() const { Particle* r = new Particle(*this); r->loadRenderItem(); return r;};

	virtual void loadRenderItem() { renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, col); };

	virtual std::list<Particle*> onDeath() { return std::list<Particle*>(); };

	void clearForce() { force *= 0; }
	
	void addForce(const Vector3& f) { force += f; }

	void setAcceleration(Vector3 a) { acc = a; };


	void setVelocity(Vector3 v) { vel = v; };
	void setPosition(Vector3 p) { pose = physx::PxTransform(p.x, p.y, p.z); };

	void setTime(int t) { remainingTime = t; };

	//void setColor(Vector4 c) { col = c; renderItem->color. };

	Vector3 getVelocity() { return vel; };

	Vector3 getPosition() { return pose.p; };

	double getMass() { return mass; };

	double getInvMass() { return inverseMass; };

	double getTime() { return remainingTime; };

	virtual int getType() { return -1; };

protected:
	Vector3 vel;
	Vector3 acc = {0.0, 0.0, 0.0};
	Vector3 force = {0.0, 0.0, 0.0};
	Vector4 col;
	double mass;
	double inverseMass;
	double damp;
	double size;
	double volume;
	double remainingTime;
	physx::PxTransform pose; // Pasar la direccion de la pose a RenderItem para que se actualice automaticamente 
	RenderItem* renderItem;
private:
	
};