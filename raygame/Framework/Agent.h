#pragma once
#include "Actor.h"
#include "Blackboard.h"
#include "DynamicArray.h"
#include "List.h"

class Behavior;

class Agent : public Actor
{
private:
	DynamicArray<Behavior*> m_behaviors;
	Blackboard* m_blackboard;
public:
	Agent();
	Agent(float x, float y);
	Agent(Behavior* behaviors[], int length);

	void addBehavior(Behavior* behavior);
	bool removeBehavior(Behavior* behavior);

	Behavior* getBehavior(Behavior* behavior);
	Behavior* getBehavior(int index);
	Blackboard* getBlackboard() { return m_blackboard; }

	void start() override;
	void update(float deltaTime) override;
};
