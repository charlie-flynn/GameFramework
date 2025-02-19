#include "Agent.h"
#include "List.h"

Agent::Agent() : Actor()
{
	behaviorCount = 0;
}

Agent::Agent(Component* behaviors[], int length) : Actor()
{
	behaviorCount = length;

	for (int i = 0; i < length; i++)
	{
		addComponent(behaviors[i]);
	}
}
