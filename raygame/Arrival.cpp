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

	float distance = (getTargetPosition() - getOwner()->getTransform()->getWorldPosition()).getMagnitude();


	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - getOwner()->getTransform()->getWorldPosition()) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = (desiredDirection - getOwner()->getVelocity());

	if (distance > getOwner()->getMaxVelocity() / 2)
		getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);
	else
		getOwner()->setVelocity(getOwner()->getVelocity() - (getOwner()->getVelocity().getNormalized() * 0.14f / getWeight()) * deltaTime);
}
