#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <typeinfo>
#include <string>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"
#include "Rocket.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"

#include "StaticRigidbody.h"
#include "DinamicRigidbody.h"

#include "ParticleSystem.h"
#include "FireworkSystem.h"
#include "ContinuousParticleSystem.h"
#include "SpringParticleSystem.h"

#include "WindForceGenerator.h"
#include "VortexGenerator.h"
#include "ExplosionForceGenerator.h"

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

// Creamos el suelo
//physx::PxTransform floorPose = physx::PxTransform({ 0.0, 0.0, 0.0 });
//RenderItem* f;

// Creamos los sistemas de particulas
std::vector<ParticleSystem*> particleSystems;
ParticleSystem* bullets;
SpringParticleSystem* springs;
FireworkSystem* fireworks;

// Sistemas de fuerzas
WindForceGenerator* windGenerator;
VortexGenerator* vortex;
ExplosionForceGenerator* explosion;

// Aceleracion de los cohetes
double rocketJet = 10;

StaticRigidbody* suelo;
DinamicRigidbody* objeto;

// Initialize physics engine
void initPhysics(bool interactive)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	//_CrtSetBreakAlloc(1570);

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

	gScene = gPhysics->createScene(sceneDesc);

	physx::PxTransform floorPose = physx::PxTransform({ 0.0, 0.0, 0.0 });
	suelo = new StaticRigidbody(gPhysics, gScene, floorPose, gMaterial, PxBoxGeometry(1000.0, 10.0, 1000.0), { 0.5, 1.0, 0.2, 1.0 });

	PxShape* s = gPhysics->createShape(PxBoxGeometry(100.0, 10.0, 100.0), *gMaterial);
	suelo->getRigidbody()->attachShape(*s);
	gScene->addActor(*suelo->getRigidbody());

	RenderItem* renderItem = new RenderItem(s, suelo->getRigidbody(), { 0.5, 1.0, 0.2, 1.0 });

	physx::PxTransform objetoPose = physx::PxTransform({ 0.0, 100.0, 0.0 });
	objeto = new DinamicRigidbody(gPhysics, gScene, objetoPose, gMaterial, PxBoxGeometry(10.0, 10.0, 10.0), { 0.5, 1.0, 0.2, 1.0 });

	PxShape* os = gPhysics->createShape(PxBoxGeometry(10.0, 10.0, 10.0), *gMaterial);
	objeto->getRigidbody()->attachShape(*os);
	gScene->addActor(*objeto->getRigidbody());

	RenderItem* objetoRenderItem = new RenderItem(os, objeto->getRigidbody(), { 1.0, 0.0, 0.0, 1.0 });

}

	
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	// Iteramos a traves de los sistemas de particulas para actualizarlos
	for (ParticleSystem* system : particleSystems) system->update(t);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	for (ParticleSystem* system : particleSystems) delete system;
	particleSystems.clear();

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