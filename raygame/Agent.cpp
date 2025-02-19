#include "Agent.h"

Agent::Agent() : Actor()
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
