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

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	MathLibrary::Vector2 targetVelocity = getTargetActor()->getVelocity();
	MathLibrary::Vector2 ownerPosition = ownerTransform->getWorldPosition();
	MathLibrary::Vector2 ownerVelocity = owner->getVelocity();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(ownerPosition - (getTargetPosition() + targetVelocity)) * owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection + ownerVelocity;

	owner->setVelocity(ownerVelocity + (steeringForce * getWeight()) * deltaTime);
}
