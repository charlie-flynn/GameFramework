#pragma once
#include "Behavior.h"

class Pursue : public Behavior
{
public:
	Pursue(Actor* owner, float weight, Actor* targetActor = nullptr);

	void update(float deltaTime) override;
};