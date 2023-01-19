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
#include "FoamSystem.h"

#include "RigidbodySystem.h"
#include "BoatSystem.h"
#include "BoyaSystem.h"

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
FoamSystem* foamSystem;
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

BoatSystem* boatSystem;
BoyaSystem* boyaSystem;

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

	windGenerator = new WindForceGenerator({ -20.0, 0.0, 8.0 }, 0.1, 0.001, { 0.0, 100.0, 0.0 }, 500.0, 500.0);

	physx::PxTransform* boatPose = new physx::PxTransform({ 0.0, 5, 0.0 });
	boat = new DinamicRigidbody(gPhysics, gScene, *boatPose, gMaterial, new PxBoxGeometry(10.0, 1.6, 6.0), { 0.2, 0.1, 0.0, 1.0 }, 10e6, 25);

	CameraTarget* t = new CameraTarget(boat->getRigidbody());

	debugSystem = new ParticleSystem();
	boatSystem = new BoatSystem(boat, gPhysics, windGenerator, debugSystem);
	boyaSystem = new BoyaSystem(gPhysics, boat);

	water = new Particle({ 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1e6, 0.99, { 0.0, 0.25, 0.35, 1.0 }, 1e6, new physx::PxBoxGeometry(10000.0, 2.5, 10000.0));

	waterSystem = new ParticleSystem();
	cloudSystem = new CloudSystem(boat, {15, 15, 30}, {2000, 10, 2000}, 200, 25, 1);
	foamSystem = new FoamSystem(boat, water);

	waterSystem->addParticle(water);

	cloudSystem->setGravity({ 0.0, 0.0, 0.0 });

	cloudSystem->addForceGenerator(windGenerator);

	particleSystems.push_back(cloudSystem);
	particleSystems.push_back(debugSystem);

	foamSystem->addForceGenerator(new BuoyancyForceGenerator(1, 1000.0, water, foamSystem));
	foamSystem->setGravity({ 0.0, -1, 0.0 });
	foamSystem->generateContinously(true);

	fireworks = new FireworkSystem({0, 0, 0});

	particleSystems.push_back(waterSystem);
	particleSystems.push_back(foamSystem);
	particleSystems.push_back(fireworks);

	BuoyancyForceGeneratorRB* buoyancy = new BuoyancyForceGeneratorRB(10, 1000.0, water, debugSystem);

	boatSystem->addForceGenerator(buoyancy);

	RBSystems.push_back(boatSystem);
	RBSystems.push_back(boyaSystem);

	boyaSystem->getBoya()->getRigidbody()->setName("Boya");
	boyaSystem->repositionBoya();

	windGenerator->setVelocity(windGenerator->getVelocity().magnitude() * (boyaSystem->getBoyaPosition() - boat->getPosition()).getNormalized());
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

	switch (toupper(key))
	{
	case 'D':
	{
		boatSystem->changeRudderDirection(1);
		break;
	}
	case 'A':
	{
		boatSystem->changeRudderDirection(-1);
		break;
	}
	case 'E':
	{
		boatSystem->rotateSail(PxQuat(-PxPi / 16, PxVec3(0, 1, 0)));
		break;
	}
	case 'Q':
	{
		boatSystem->rotateSail(PxQuat(PxPi / 16, PxVec3(0, 1, 0)));
		break;
	}
	case 'S':
	{
		boatSystem->throwAnchor();
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	if(actor1->getName() == boyaSystem->getBoya()->getRigidbody()->getName() || actor2->getName() == boyaSystem->getBoya()->getRigidbody()->getName())
	{
		fireworks->setPosition(boyaSystem->getBoyaPosition());
		fireworks->createFirework();

		boyaSystem->repositionBoya();

		Vector3 windDir = Vector3(boyaSystem->getBoyaPosition().x - boat->getPosition().x, 0, boyaSystem->getBoyaPosition().z - boat->getPosition().z).getNormalized();
		windGenerator->setVelocity(windGenerator->getVelocity().magnitude() * windDir);
	}
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