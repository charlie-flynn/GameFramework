#pragma once
#include "Behavior.h"

class Wander : public Behavior
{
private:
	float m_wanderRadius;
	float m_wanderDistance;
public:
	Wander();
	Wander(Actor* owner, float weight, float wanderRadius, float wanderDistance);

	void start() override;
	void update(float deltaTime) override;

	float getWanderRadius() { return m_wanderRadius; }
	void setWanderRadius(float value) { m_wanderRadius = value; }

	float getWanderDistance() { return m_wanderDistance; }
	void setWanderDistance(float value) { m_wanderDistance = value; }
};
