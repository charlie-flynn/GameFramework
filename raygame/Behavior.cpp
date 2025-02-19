#include "Behavior.h"
#include "Actor.h"
#include "Transform2D.h"

Behavior::Behavior(Actor* owner, float weight, Actor* targetActor) : Component(owner), m_targetActor(targetActor)
{
	setWeight(weight);
}

Behavior::Behavior(Actor* owner, float weight, MathLibrary::Vector2 targetPosition) : Component(owner), m_targetPosition(targetPosition)
{
	setWeight(weight);
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
