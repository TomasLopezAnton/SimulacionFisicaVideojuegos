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

#include "GaussianBodyGenerator.h"

#include "StaticRigidbody.h"
#include "DinamicRigidbody.h"

#include "ParticleSystem.h"
#include "FireworkSystem.h"
#include "ContinuousParticleSystem.h"
#include "SpringParticleSystem.h"
#include "CloudSystem.h"

#include "RigidbodySystem.h"

#include "WindForceGenerator.h"
#include "VortexGenerator.h"
#include "ExplosionForceGenerator.h"

#include "RBWindForceGenerator.h"
#include "BuoyancyForceGeneratorRB.h"

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
std::vector<RigidbodySystem*> RBSystems;

ParticleSystem* bullets;
ParticleSystem* waterSystem;
CloudSystem* cloudSystem;
ParticleSystem* debugSystem;
SpringParticleSystem* springs;
FireworkSystem* fireworks;

// Sistemas de fuerzas
WindForceGenerator* windGenerator;
VortexGenerator* vortex;
ExplosionForceGenerator* explosion;

GaussianParticleGenerator* cloudGenerator;


RBWindForceGenerator* RBwindGenerator;

// Aceleracion de los cohetes
double rocketJet = 10;

Particle* water;

StaticRigidbody* suelo;
DinamicRigidbody* boat;
GaussianBodyGenerator* generator;

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

	waterSystem = new ParticleSystem();
	debugSystem = new ParticleSystem();
	cloudSystem = new CloudSystem({15, 15, 30}, {1000, 10, 1000}, 200, 0.5);

	cloudSystem->setGravity({ 0.0, 0.0, 0.0 });

	cloudSystem->addForceGenerator(new WindForceGenerator({ -20.0, 0.0, 8.0 }, 0.1, 0.001, { 0.0, 100.0, 0.0 }, 500.0, 500.0));

	particleSystems.push_back(cloudSystem);
	particleSystems.push_back(debugSystem);

	water = new Particle({ 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1e6, 0.99, { 0.0, 0.25, 0.35, 1.0 }, 1e6, new physx::PxBoxGeometry(10000.0, 1.8, 10000.0));
	waterSystem->addParticle(water);

	particleSystems.push_back(waterSystem);

	RigidbodySystem* boatSystem = new RigidbodySystem();

	physx::PxTransform* boatPose = new physx::PxTransform({ 0.0, 5, 0.0 });
	CameraTarget* t = new CameraTarget(boatPose);
	boat = new DinamicRigidbody(gPhysics, gScene, *boatPose, gMaterial, new PxBoxGeometry(10.0, 1.59, 6.0), { 0.2, 0.1, 0.0, 1.0 }, 10e6);
	boat->setMass(1000);

	boatSystem->addRigidbody(boat);

	BuoyancyForceGeneratorRB* buoyancy = new BuoyancyForceGeneratorRB(1.0, 1000.0, water, debugSystem);

	boatSystem->addForceGenerator(buoyancy);

	//physx::PxTransform floorPose = physx::PxTransform({ 0.0, 0.0, 0.0 });
	//suelo = new StaticRigidbody(gPhysics, gScene, floorPose, gMaterial, new PxBoxGeometry(1000.0, 10.0, 1000.0), { 0.5, 1.0, 0.2, 1.0 }, 1e6);

	//physx::PxTransform objetoPose = physx::PxTransform({ 0.0, -1000.0, 0.0 });
	//objeto = new DinamicRigidbody(gPhysics, gScene, objetoPose, gMaterial, new PxBoxGeometry(1.0, 1.0, 1.0), { 1.0, 0.0, 0.0, 1.0 }, 10);

	//RigidbodySystem* cubes = new RigidbodySystem();

	RBSystems.push_back(boatSystem);

	//generator = new GaussianBodyGenerator("Gen", objeto, { 0.0, 150.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.1, 0.1, 0.1 }, { 20, 0.1, 20 }, 1);
	//cubes->addGenerator(generator);

	//RBwindGenerator = new RBWindForceGenerator({ -100.0, 0.0, -100.0 }, 0.1, 0.001, { 0.0, 40.0, 0.0 }, 40.0, 50.0);
	//boatSystem->addForceGenerator(RBwindGenerator);

	//cubes->addForceGenerator(RBwindGenerator);
}

	
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	// Iteramos a traves de los sistemas de particulas para actualizarlos
	for (ParticleSystem* system : particleSystems) system->update(t);

	for (RigidbodySystem* system : RBSystems) system->update(t);

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
	case 'O':
	{
		boat->rotate({0.9999999, 0.0087265, 0, 0});
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