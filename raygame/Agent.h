#pragma once
#include "Actor.h"
#include "DynamicArray.h"
#include "List.h"

class Behavior;

class Agent : public Actor
{
private:
	DynamicArray<Behavior*> m_behaviors;
public:
	Agent();
	Agent(Behavior* behaviors[], int length);

	void addBehavior(Behavior* behavior);
	bool removeBehavior(Behavior* behavior);
	Behavior* getBehavior(Behavior* behavior);
};