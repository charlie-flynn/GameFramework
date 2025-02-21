#pragma once
#include "Behavior.h"

class Flee : public Behavior
{
public:
	Flee();
	Flee(Actor* owner, float weight = 0, Actor* targetActor = nullptr);
	Flee(Actor* owner, float weight = 0, MathLibrary::Vector2 targetPosition = { 0, 0 });
	void update(float deltaTime) override;
};