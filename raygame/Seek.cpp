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
	Behavior::update(deltaTime);

	// if no weight, do nothing
	if (!getWeight())
	{
		return;
	}

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getOwner()->getTransform()->getWorldPosition() - getTargetPosition()) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 turnForce = getOwner()->getVelocity() + (desiredDirection - getOwner()->getVelocity()) * getWeight();

	getOwner()->setVelocity((getOwner()->getVelocity() + turnForce) * getWeight() * deltaTime);
}
