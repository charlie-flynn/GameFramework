#include "Wander.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"
#include <random>
#include <cmath>
#include <iostream>

Wander::Wander() : Behavior(), m_wanderRadius(0.0f), m_wanderDistance(0.0f)
{
}

Wander::Wander(Actor* owner, float weight, float wanderRadius, float wanderDistance) : Behavior(owner, weight, {0, 0}), m_wanderRadius(wanderRadius), m_wanderDistance(wanderDistance)
{
}

void Wander::start()
{
	// get a random value between -1 and 1 for both the X and Y coordinates
	int randomIntX = (rand() % 2001) - 1000;
	int randomIntY = (rand() % 2001) - 1000;

	MathLibrary::Vector2 randomTarget = { (float)randomIntX / 1000, (float)randomIntY / 1000 };

	randomTarget.normalize();

	randomTarget = randomTarget * m_wanderRadius;

	randomTarget = randomTarget + getOwner()->getTransform()->getWorldPosition();
	randomTarget = randomTarget + (getOwner()->getTransform()->getForward() * m_wanderDistance);

	setTargetPosition(randomTarget);
}

void Wander::update(float deltaTime)
{
	// if no weight, do nothing
	if (!getWeight())
		return;

	float distanceToTarget = (getTargetPosition() - getOwner()->getTransform()->getWorldPosition()).getMagnitude();

	Actor* owner = getOwner();
	Transform2D* ownerTransform = owner->getTransform();

	if (distanceToTarget <= 10.0f || distanceToTarget >= m_wanderRadius + m_wanderDistance)
	{
		// get a random value between -1 and 1 for both the X and Y coordinates
		int randomIntX = (rand() % 2001) - 1000;
		int randomIntY = (rand() % 2001) - 1000;

		MathLibrary::Vector2 randomTarget = { (float)randomIntX / 1000, (float)randomIntY / 1000 };

		randomTarget.normalize();

		randomTarget = randomTarget * m_wanderRadius;

		randomTarget = randomTarget + owner->getTransform()->getWorldPosition();
		randomTarget = randomTarget + (owner->getTransform()->getForward() * m_wanderDistance);

		setTargetPosition(randomTarget);
	}


	MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerTransform->getWorldPosition()) * owner->getMaxVelocity();
	MathLibrary::Vector2 steeringForce = desiredDirection - owner->getVelocity();

	owner->setVelocity(owner->getVelocity() + (steeringForce * getWeight()) * deltaTime);

}
