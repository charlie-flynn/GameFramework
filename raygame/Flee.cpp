#include "Flee.h"
#include "Actor.h"
#include "Transform2D.h"

Flee::Flee() : Behavior()
{
}

Flee::Flee(Actor* owner, float weight, Actor* targetActor) : Behavior(owner, weight, targetActor)
{
}

Flee::Flee(Actor* owner, float weight, MathLibrary::Vector2 targetPosition) : Behavior(owner, weight, targetPosition)
{
}

void Flee::update(float deltaTime)
{
	// if no weight, do nothing
	if (!getWeight())
	{
		return;
	}

	Behavior::update(deltaTime);

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(ownerTransform->getWorldPosition() - getTargetPosition())* owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - owner->getVelocity();

	owner->setVelocity(owner->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
