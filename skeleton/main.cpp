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
#include "ParticleSystem.h"
#include "FireworkSystem.h"

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
ParticleSystem* font;
FireworkSystem* fireworks;

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

	#pragma region Inicializacion Suelo
	// Inicializamos y registramos el suelo
	f = new RenderItem(CreateShape(physx::PxBoxGeometry(1000.0, 1.0, 1000.0)), &floorPose, { 0.8, 0.8, 0.0, 1.0 });
	RegisterRenderItem(f);
	#pragma endregion

	#pragma region Inicializacion Bullets
	// Inicializamos el sistema de particulas que gestiona las particulas generales
	bullets = new ParticleSystem();
	particleSystems.push_back(bullets);
	#pragma endregion

	#pragma region Inicializacion Fuente
	// Inicializamos la fuente
	font = new ParticleSystem();

	Particle* p = new Particle({ 0.0, -100000.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1.0, 0.95, { 0.0, 0.0, 0.0 }, 20.0, { 0.1, 0.2, 1.0, 1.0 }, 1.0);

	font->addGenerator(new GaussianParticleGenerator((std::string)"FontGenerator", p, { 0.0, 0.0, 0.0 }, { 10.0, 30.0, 0.0 }, { 1.0, 1.0, 1.0 }, { 0.1, 0.1, 0.1 }, 3));
	particleSystems.push_back(font);
	#pragma endregion

	#pragma region Inicializacion Fireworks
	// Inicializamos los fuegos artificiales
	fireworks = new FireworkSystem();
	particleSystems.push_back(fireworks);
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

	DeregisterRenderItem(f);
	delete f;


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
	case 'C': // Hacemos que la fuente empieze y pare de generar
		font->generateContinously(!font->getGenerating());
		break;
	case 'F': // Creamos la primera particula de los fuegos artificiales
		fireworks->createFirework();
		break;
	case 'R': // Creamos un cohete
		bullets->addParticle(new Rocket(GetCamera()->getEye() + 2 * GetCamera()->getDir(), rocketJet * GetCamera()->getDir(), 2000.0, 0.1, { 1.0, 0.0, 0.0 }, 8));
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