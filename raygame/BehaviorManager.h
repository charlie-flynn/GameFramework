#pragma once
#include "Component.h"
#include "DynamicArray.h"

class Actor;
class Behavior;

class BehaviorManager : public Component
{
private:
	DynamicArray<Behavior*> m_behaviors;
public:
	BehaviorManager();
	BehaviorManager(Actor* owner);
	void start() override;
	void update(float deltaTime) override;
	void end() override;
};
