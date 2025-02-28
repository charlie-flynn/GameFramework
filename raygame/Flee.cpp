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

	owner->setVelocity(owner->getVelocity() + ((seekToPoint() * -1) * getWeight()) * deltaTime);
}
