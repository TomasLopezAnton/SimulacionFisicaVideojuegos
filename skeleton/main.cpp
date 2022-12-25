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
physx::PxTransform floorPose = physx::PxTransform({ 0.0, 0.0, 0.0 });
RenderItem* f;

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

	#pragma region Inicializacion Sistema Muelles
	springs = new SpringParticleSystem();
	springs->setGravity({ 0.0, -0.0, 0.0 });
	particleSystems.push_back(springs);
	#pragma endregion

	#pragma region Inicializacion Fuerzas
	windGenerator = new WindForceGenerator({ -100.0, 0.0, -100.0 }, 0.1, 0.001, { 0.0, 0.0, 0.0 }, 2.0, 100.0);
	vortex = new VortexGenerator(0.2, { -0.0, 0.0,  -0.0 }, 100);
	explosion = new ExplosionForceGenerator(200, 2, Vector3(20.0, 5.0, 20.0), 0.1, 240.0);
	#pragma endregion

	gScene = gPhysics->createScene(sceneDesc);

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
	//case 'V': // Activa una rafaga de viento entre las dos alturas especificadas
	//	for (ParticleSystem* p : particleSystems)
	//	{
	//		if (p->containsForceGenerator(windGenerator)) p->removeForceGenerator(windGenerator);
	//		else p->addForceGenerator(windGenerator);
	//	}
		break;
	case 'T': // Activa el remolino
		for(ParticleSystem* p : particleSystems)
		{
			if (p->containsForceGenerator(vortex)) p->removeForceGenerator(vortex);
			else p->addForceGenerator(vortex);
		}
		break;
	case 'E': // Activa una explosion que crece con el tiempo
		for (ParticleSystem* p : particleSystems)
		{
			if (p->containsForceGenerator(explosion)) p->removeForceGenerator(explosion);
			else
			{
				explosion->setRadius(0.0);
				p->addForceGenerator(explosion);
			}
		}
		break;
	case 'G': // Toggle Gravity
	{
		Vector3 grav = springs->getGravity();
		if (grav.y == 0.0) springs->setGravity({ grav.x, -10, grav.z });
		else springs->setGravity({ grav.x, 0.0, grav.z });
		break;
	}
	//case 'M':
	//	springs->generateDualSpring();
	//	break;
	//case 'N':
	//	springs->generateAnchoredSpring();
	//	break;	
	//case 'B':
	//	springs->generateBungeeSpring();
	//	break;
	case 'L':
		springs->generateConstraintsSlinky();
		break;
	case'F':
		springs->generateBuoyantParticle();
		break;	
	case'Z':
		springs->generateConstraintsSpring();
		break;
	case'C':
		springs->clearSystem();
		break;
	case'R':
		springs->generateRope();
		break;
	case'V':
		springs->velRedParticle({10, 0, 10});
		break;
	case'M':
		springs->velRedParticle({ -10, 0, 0 });
		break;
	case'N':
		springs->velRedParticle({ 10, 0, 0 });
		break;
	case'B':
		springs->stopRedParticle();
		break;
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