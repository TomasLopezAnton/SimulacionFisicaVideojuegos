#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <typeinfo>
#include <string>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Cannonball.h"
#include "Fireball.h"
#include "Laser.h"
#include "Rocket.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ParticleSystem.h"
#include "FireworkSystem.h"


#include <iostream>
#include <istream>



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

physx::PxTransform floorPose = physx::PxTransform({ 0.0, 0.0, 0.0 });
RenderItem* f;

physx::PxTransform targetPose = physx::PxTransform({ 20.0, 60.0, 0.0 });
RenderItem* target;

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
GaussianParticleGenerator* generator;

std::vector<ParticleSystem*> particleSystems;
ParticleSystem* font;
FireworkSystem* fireworks;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	f = new RenderItem(CreateShape(physx::PxBoxGeometry(1000.0, 1.0, 1000.0)), &floorPose, { 0.8, 0.8, 0.0, 1.0 });
	RegisterRenderItem(f);

	font = new ParticleSystem();

	Particle* p = new Particle({ 0.0, -100000.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.95, { 0.1, 0.2, 1.0, 1.0 });
	p->setGravity({ 0.0, -10, 0.0 });

	font->addGenerator(new GaussianParticleGenerator((std::string)"FontGenerator", p, { 0.0, 0.0, 0.0 }, { 10.0, 30.0, 0.0 }, { 1.0, 1.0, 1.0 }, { 0.1, 0.1, 0.1 }, 3));
	particleSystems.push_back(font);

	fireworks = new FireworkSystem();
	particleSystems.push_back(fireworks);

	gScene = gPhysics->createScene(sceneDesc);
}

	
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	while (bullets.size() > 10000)
	{
		Particle* x = bullets.front();
		bullets.erase(bullets.begin());
		delete x;
	}

	for (ParticleSystem* system : particleSystems) system->update(t);

	for(Particle* c: bullets) c->integrate(t);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	laserBeam.clear();
	bullets.clear();

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
	case 'R':
		bullets.push_back(new Rocket(GetCamera()->getEye() + 2 * GetCamera()->getDir(), fireVelocity * GetCamera()->getDir(), 0.1, {1.0, 0.0, 0.0}));
		break;
	case 'C':
		font->generateContinously(!font->getGenerating());
		break;
	case 'K':
		fireworks->createFirework();
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