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

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	MathLibrary::Vector2 targetVelocity = getTargetActor()->getVelocity();

	owner->setVelocity(owner->getVelocity() + (seekToPoint(getTargetPosition() + targetVelocity) * getWeight()) * deltaTime);
}
