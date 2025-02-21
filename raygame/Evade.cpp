#include "Evade.h"
#include "Actor.h"
#include "Transform2D.h"

Evade::Evade(Actor* owner, float weight, Actor* target) : Behavior(owner, weight, target)
{
}

void Evade::update(float deltaTime)
{
	// if no weight or target actor, do nothing
	if (!getWeight() || !getTargetActor())
	{
		return;
	}

	Behavior::update(deltaTime);

	MathLibrary::Vector2 targetVelocity = getTargetActor()->getVelocity();
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(ownerPosition - (getTargetPosition() + targetVelocity)) * getOwner()->getMaxVelocity() - getOwner()->getVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection + getOwner()->getVelocity();

	getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
