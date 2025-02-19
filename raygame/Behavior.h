#pragma once
#include "Vector2.h"
#include "Component.h"

typedef MathLibrary::Vector2 Vector2;

class Behavior : public Component
{
private:
	float m_weight;
	Vector2 m_target;
public:
	Behavior();
	Behavior(float weight);

	float getWeight() { return m_weight; }
	void setWeight(float value);

	Vector2 getTarget() { return m_target; }
	void setTarget(Vector2 value) { m_target = value; }
	void setTarget(float x, float y) { m_target.x = x; m_target.y = y; }

	void virtual calculate(float deltaTime) {}
};