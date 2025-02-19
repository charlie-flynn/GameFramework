#pragma once
#include "Vector2.h"
#include "Component.h"

class Behavior : public Component
{
private:
	float m_weight;
	MathLibrary::Vector2 m_targetPosition;
	Actor* m_targetActor;
public:
	Behavior(Actor* owner, float weight = 0, Actor* targetActor = nullptr);
	Behavior(Actor* owner, float weight = 0, MathLibrary::Vector2 targetPosition = {0, 0});

	float getWeight() { return m_weight; }
	void setWeight(float value);

	MathLibrary::Vector2 getTargetPosition() { return m_targetPosition; }
	void setTargetPosition(MathLibrary::Vector2 value) { m_targetPosition = value; }
	void setTargetPosition(float x, float y) { m_targetPosition.x = x; m_targetPosition.y = y; }

	void setTargetActor(Actor* value) { m_targetActor = value; }

	void update(float deltaTime) override;
};