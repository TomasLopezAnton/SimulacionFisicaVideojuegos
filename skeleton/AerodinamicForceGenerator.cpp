#include "AerodinamicForceGenerator.h"

void AerodinamicForceGenerator::updateForce(Rigidbody* p, double duration)
{
	position = sail->getPosition();
	orientation = sail->getRotation();
	windVel = wind->getVelocity();

	float pressure = airDensity * (windVel.magnitude() * windVel.magnitude());
	float area = dimensions.y * dimensions.z;

	Vector3 normalVector = { 1, 0, 0 };
	normalVector = -orientation.rotate(normalVector).getNormalized();
	float windForce = pressure * area * windVel.getNormalized().dot(normalVector);

	Vector3 boatDir = boat->getRotation().rotate({ 1, 0, 0 });
	float forwardForce = Vector3(min(abs(boatDir.x + normalVector.x), 1), 0, min(abs(boatDir.z + normalVector.z), 1)).magnitude() * windForce;
	float torqueForce = Vector3(min(abs(rudderDirection->x + normalVector.x), 1), 0, min(abs(rudderDirection->z + normalVector.z), 1)).magnitude() * windForce;

	boat->addForce(boatDir * forwardForce);

	boat->addTorque(rudderPosition * torqueForce);

	std::cout << forwardForce << "\n";
	std::cout << torqueForce << "\n";

	Vector3 torque = rudderPosition * torqueForce;
}