#include "Pursue.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"

Pursue::Pursue(Actor* owner, float weight, Actor* targetActor) : Behavior(owner, weight, targetActor)
{
}

void Pursue::update(float deltaTime)
{
	// if no weight or target actor, do nothing
	if (!getWeight() || !getTargetActor())
	{
		return;
	}

	Behavior::update(deltaTime);

	MathLibrary::Vector2 targetVelocity = getTargetActor()->getVelocity();
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize((getTargetPosition() + targetVelocity) - ownerPosition) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - getOwner()->getVelocity();

	getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
