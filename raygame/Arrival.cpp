#include "Arrival.h"
#include "Transform2D.h"
#include "Vector2.h"
#include "Actor.h"
#include <cmath>

Arrival::Arrival()
{
}

Arrival::Arrival(Actor* owner, float weight, Actor* targetActor) : Behavior(owner, weight, targetActor)
{
}

Arrival::Arrival(Actor* owner, float weight, MathLibrary::Vector2 targetPosition) : Behavior(owner, weight, targetPosition)
{
}

void Arrival::update(float deltaTime)
{
	// if no weight, do nothing
	if (!getWeight())
	{
		return;
	}

	Behavior::update(deltaTime);

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();
	MathLibrary::Vector2 ownerVelocity = owner->getVelocity();

	float distance = (getTargetPosition() - ownerTransform->getWorldPosition()).getMagnitude();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerTransform->getWorldPosition()) * owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - ownerVelocity;

	owner->setVelocity(ownerVelocity + (steeringForce * getWeight() * fmin(distance, 1.0f)) * deltaTime);
}
