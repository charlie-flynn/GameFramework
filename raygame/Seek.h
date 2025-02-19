#pragma once

#include "Behavior.h"

class Seek : public Behavior
{
public:
	Seek();
	Seek(Actor* owner, float weight = 0, Actor* targetActor = nullptr);
	Seek(Actor* owner, float weight = 0, MathLibrary::Vector2 targetPosition = { 0, 0 });
	void update(float deltaTime) override;
};
