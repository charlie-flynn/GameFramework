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

	float distance = (getTargetPosition() - ownerTransform->getWorldPosition()).getMagnitude();


	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerTransform->getWorldPosition()) * owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = (desiredDirection - owner->getVelocity());

	if (distance > owner->getMaxVelocity() / 2)
		owner->setVelocity(owner->getVelocity() + (steeringForce * getWeight()) * deltaTime);
	else
		owner->setVelocity(owner->getVelocity() - (owner->getVelocity().getNormalized() * 0.14f / getWeight()) * deltaTime);
}
