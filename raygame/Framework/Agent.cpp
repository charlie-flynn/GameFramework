#include "Agent.h"
#include "Transform2D.h"

Agent::Agent() : Actor(), m_blackboard(new Blackboard(this))
{
}

Agent::Agent(float x, float y, int ID) : Actor(x, y, ID), m_blackboard(new Blackboard(this))
{
}

Agent::Agent(Behavior* behaviors[], int length) : Actor(), m_blackboard(new Blackboard(this))
{
	for (int i = 0; i < length; i++)
	{
		addBehavior(behaviors[i]);
	}
}

void Agent::addBehavior(Behavior* behavior)
{
	addComponent((Component*)behavior);
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

Behavior* Agent::getBehavior(int index)
{
	return m_behaviors[index];
}

void Agent::start()
{
	Actor::start();
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

	// rotate and move according to the velocity
	if (getVelocity().x != 0.0f || getVelocity().y != 0.0f)
	{
		// the -2 over there is because. i need things to turn and also turn the right way :thumbsup:
		getTransform()->rotate((MathLibrary::Vector2::findAngle(getTransform()->getForward().getNormalized(), getVelocity().getNormalized()) * -2) * deltaTime);
		getTransform()->setLocalPosition(getTransform()->getLocalPosition() + getTransform()->getForward() * getVelocity().getMagnitude() * deltaTime);
	}
}
