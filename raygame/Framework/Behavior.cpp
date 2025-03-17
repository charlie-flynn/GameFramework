#include "Behavior.h"
#include "Actor.h"
#include "Transform2D.h"

Behavior::Behavior() : Component(), m_targetActor(nullptr), m_weight(0)
{
}

Behavior::Behavior(Actor* owner, float weight, Actor* targetActor) : Component(owner), m_targetActor(targetActor)
{
	setWeight(weight);
}

Behavior::Behavior(Actor* owner, float weight, MathLibrary::Vector2 targetPosition) : Component(owner), m_targetPosition(targetPosition)
{
	setWeight(weight);
}

MathLibrary::Vector2 Behavior::seekToPoint(MathLibrary::Vector2 point)
{
	if (point == MathLibrary::Vector2(0, 0))
		point = getTargetPosition();

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(point - ownerTransform->getWorldPosition()) * owner->getMaxVelocity();
	return desiredDirection - owner->getVelocity();
}

void Behavior::setWeight(float value)
{
	if (value > 1)
		m_weight = 1;
	else if (value < 0)
		m_weight = 0;
	else
		m_weight = value;
}

void Behavior::update(float deltaTime)
{
	// if there is a target actor, update the target position to be the target actor's position
	if (m_targetActor)
		m_targetPosition = m_targetActor->getTransform()->getWorldPosition();
}
