#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <typeinfo>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Cannonball.h"
#include "Fireball.h"
#include "Laser.h"

#include <iostream>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

std::vector<Particle*> bullets;
std::vector<Laser*> laserBeam;

Particle* p;
Vector3 particleVelocity = { 25.0, 0.0, 0.0 };
double fireVelocity = 10;
double laserVelocity = 3000;
Vector3 particleAcceleration = { 0.0, 1.0, 0.0 };
Vector3 initialPos = { 0.0, 0.0, 0.0 };

double particleDamping = 1;
bool firingLaser = false;
int maxLaserParticles = 100;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;


	gScene = gPhysics->createScene(sceneDesc);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	if (firingLaser)
	{
		Laser* las = new Laser(GetCamera()->getEye() + 5 * GetCamera()->getDir(), laserVelocity * GetCamera()->getDir(), 1.0);
		bullets.push_back(las);
		laserBeam.push_back(las);
	}

	int l = -1;
	int pos = 0;

	for(Particle* c: bullets)
	{
		if (c->isLaser() && l < 0) l = pos;

		c->integrate(t);
		pos++;
	}

	if (laserBeam.size() > maxLaserParticles) 
	{
		Laser* x = laserBeam.front();
		laserBeam.erase(laserBeam.begin());
		bullets.erase(bullets.begin() + l);
		delete x;
	}

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete p;
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'B': 
		bullets.push_back(new Cannonball(GetCamera()->getEye(), 25 * GetCamera()->getDir(), particleDamping));
		break;	
	case 'F': 
		bullets.push_back(new Fireball(GetCamera()->getEye() + 2 * GetCamera()->getDir(), fireVelocity * GetCamera()->getDir(), 0.95));
		break;	
	case 'L':
		firingLaser = !firingLaser;
		break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}