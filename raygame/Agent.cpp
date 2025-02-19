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
}

bool Agent::removeBehavior(Behavior* behavior)
{
    return false;
}

Behavior* Agent::getBehavior(Behavior* behavior)
{
    return nullptr;
}
