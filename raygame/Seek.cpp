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

	Behavior::update(deltaTime);

	owner->setVelocity(owner->getVelocity() + (seekToPoint() * getWeight()) * deltaTime);
}
