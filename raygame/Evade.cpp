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

	owner->setVelocity(owner->getVelocity() + ((seekToPoint(getTargetPosition() + targetVelocity) * -1) * getWeight()) * deltaTime);
}
