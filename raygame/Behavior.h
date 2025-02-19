#pragma once

class Behavior
{
private:
	float m_weight;
public:
	Behavior();
	Behavior(float weight);
	~Behavior() = default;

	float getWeight() { return m_weight; }
	void setWeight(float value);
	void virtual calculate(float deltaTime) {}
};