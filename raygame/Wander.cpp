#include "Wander.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"
#include <random>
#include <cmath>

Wander::Wander() : Behavior(), m_wanderRadius(0.0f)
{
}

Wander::Wander(Actor* owner, float weight, float wanderRadius, float wanderDistance) : Behavior(owner, weight, nullptr), m_wanderRadius(wanderRadius), m_wanderDistance(wanderDistance)
{
}

void Wander::update(float deltaTime)
{
	// if no weight, do nothing
	if (!getWeight())
		return;

	if (sqrt((getOwner()->getTransform()->getWorldPosition().x - getTargetPosition().x) + (getOwner()->getTransform()->getWorldPosition().y - getTargetPosition().y)) <= 5)
	{
		// get a random value between -1 and 1 for both the X and Y coordinates
		int randomIntX = (rand() % 2001) - 1000;
		int randomIntY = (rand() % 2001) - 1000;

		MathLibrary::Vector2 randomTarget = { (float)randomIntX / 1000, (float)randomIntY / 1000 };

		randomTarget.normalize();

		randomTarget = randomTarget * m_wanderRadius;

		randomTarget = randomTarget + getOwner()->getTransform()->getWorldPosition() + (getOwner()->getTransform()->getForward() * m_wanderDistance);

		setTargetPosition(randomTarget);
	}


	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - getOwner()->getTransform()->getWorldPosition()) * getOwner()->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - getOwner()->getVelocity();

	getOwner()->setVelocity(getOwner()->getVelocity() + (steeringForce * getWeight()) * deltaTime);

}
