#include "Seek.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"

Seek::Seek() : Behavior()
{
}

Seek::Seek(Actor* owner, float weight, Actor* targetActor) : Behavior(owner, weight, targetActor)
{
}

Seek::Seek(Actor* owner, float weight, MathLibrary::Vector2 targetPosition) : Behavior(owner, weight, targetPosition)
{
}

void Seek::update(float deltaTime)
{
	// if no weight, do nothing
	if (!getWeight())
	{
		return;
	}

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	Behavior::update(deltaTime);

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerTransform->getWorldPosition()) * owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - owner->getVelocity();

	owner->setVelocity(owner->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
