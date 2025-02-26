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

	// ok so somehwere in this game engine there's a memory leak i think????????? and it's messing up the deceleration
	// so at least i KNOW what the hell is going on now. almost. i have no clue where the memory leak could possibly be

	if (distance > owner->getMaxVelocity() / 1.5f)
		owner->setVelocity(ownerVelocity + (steeringForce * getWeight()) * deltaTime);
	else
		owner->setVelocity(ownerVelocity - (ownerVelocity * 0.00023f / getWeight()) * deltaTime);
}
