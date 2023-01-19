#include "AerodinamicForceGenerator.h"

void AerodinamicForceGenerator::updateForce(Rigidbody* p, double duration)
{
	position = sail->getPosition();
	orientation = sail->getRotation();
	windVel = wind->getVelocity();

	float pressure = airDensity * (windVel.magnitude() * windVel.magnitude());
	float area = dimensions.y * dimensions.z;

	Vector3 normalVector = { 1, 0, 0 };
	normalVector = orientation.rotate(normalVector).getNormalized();
	float windForce = pressure * area * windVel.getNormalized().dot(normalVector);

	float torqueForce = orientation.rotate(rudderDirection->getNormalized()).z * windForce;
	float forwardForce = (abs(windForce) - abs(torqueForce)) * ((windForce > 0) - (windForce < 0));

	boat->addForce(boat->getRotation().rotate({ 1, 0, 0 }) * forwardForce);

	boat->addTorque(rudderPosition * torqueForce);
	//boat->addTorque({0, 100000, 0});

	Vector3 torque = rudderPosition * torqueForce;

	//std::cout << torque.x << " " << torque.y << " " << torque.z << "\n";
}