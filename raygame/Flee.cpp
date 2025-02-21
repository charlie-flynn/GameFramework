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

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getOwner()->getTransform()->getWorldPosition() - getTargetPosition()) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - getOwner()->getVelocity();

	getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);
}
