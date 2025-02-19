#include "Seek.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"

void Seek::update(float deltaTime)
{
	Behavior::update(deltaTime);

	// if no weight, do nothing
	if (!getWeight())
	{
		return;
	}

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getOwner()->getTransform()->getWorldPosition() - getTargetPosition());
}
