#pragma once
#include "Behavior.h"

class Evade : public Behavior
{
public:
	Evade(Actor* owner, float weight, Actor* target = nullptr);

	void update(float deltaTime) override;
};