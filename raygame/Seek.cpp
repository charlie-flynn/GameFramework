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

	Behavior::update(deltaTime);

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - getOwner()->getTransform()->getWorldPosition()) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - getOwner()->getVelocity();

	getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
