#pragma once
#include "Behavior.h"

class Arrival : public Behavior
{
public:
	Arrival();
	Arrival(Actor* owner, float weight, Actor* targetActor = nullptr);
	Arrival(Actor* owner, float weight, MathLibrary::Vector2 targetPosition = { 0, 0 });

	void update(float deltaTime) override;
};
