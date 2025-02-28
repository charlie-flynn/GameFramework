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
	Behavior();
	Behavior(Actor* owner, float weight, Actor* targetActor = nullptr);
	Behavior(Actor* owner, float weight, MathLibrary::Vector2 targetPosition = {0, 0});

	/// <summary>
	/// Performs seek behavior towards a point. If argument not inputted (or the argument happens to be 0, 0), seek to target position.
	/// </summary>
	/// <param name="point">The point to seek towards.</param>
	/// <returns>The required turning force to turn towards the point.</returns>
	MathLibrary::Vector2 seekToPoint(MathLibrary::Vector2 point = {0, 0});

	float getWeight() { return m_weight; }
	void setWeight(float value);

	MathLibrary::Vector2 getTargetPosition() { return m_targetPosition; }
	void setTargetPosition(MathLibrary::Vector2 value) { m_targetPosition = value; }
	void setTargetPosition(float x, float y) { m_targetPosition.x = x; m_targetPosition.y = y; }

	Actor* getTargetActor() { return m_targetActor; }
	void setTargetActor(Actor* value) { m_targetActor = value; }

	void update(float deltaTime) override;
};