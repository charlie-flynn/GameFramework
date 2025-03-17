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
	Agent(float x, float y);
	Agent(Behavior* behaviors[], int length);

	void addBehavior(Behavior* behavior);
	bool removeBehavior(Behavior* behavior);

	Behavior* getBehavior(Behavior* behavior);
	Behavior* getBehavior(int index);

	void start() override;
	void update(float deltaTime) override;
};
