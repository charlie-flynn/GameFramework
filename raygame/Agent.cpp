#include "Agent.h"
#include "Transform2D.h"
#include <iostream>

Agent::Agent() : Actor()
{
}

Agent::Agent(float x, float y) : Actor(x, y, "remove name soon pls")
{
}

Agent::Agent(Behavior* behaviors[], int length) : Actor()
{
	for (int i = 0; i < length; i++)
	{
		addBehavior(behaviors[i]);
	}
}

void Agent::addBehavior(Behavior* behavior)
{
	addComponent(behavior);
	m_behaviors.Add(behavior);
}

bool Agent::removeBehavior(Behavior* behavior)
{
	if (removeComponent(behavior))
	{
		m_behaviors.Remove(behavior);
		return true;
	}
	else
	{
		return false;
	}
}

Behavior* Agent::getBehavior(Behavior* behavior)
{
	for (int i = 0; i < m_behaviors.Length(); i++)
	{
		if (m_behaviors[i] == behavior)
			return m_behaviors[i];
	}
	return nullptr;
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

	// rotate and move according to the velocity
	getTransform()->rotate((MathLibrary::Vector2::findAngle(getTransform()->getForward().getNormalized(), getVelocity().getNormalized()) * -2) * deltaTime);
	std::cout << (MathLibrary::Vector2::findAngle(getTransform()->getForward().getNormalized(), getVelocity().getNormalized())) << std::endl;

	if (getVelocity().x != 0.0f || getVelocity().y != 0.0f)
		getTransform()->setLocalPosition(getTransform()->getLocalPosition() + getTransform()->getForward() * getVelocity().getMagnitude() * deltaTime);
}
