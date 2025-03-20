#include "PathBehavior.h"
#include "Actor.h"
#include "Transform2D.h"
PathBehavior::PathBehavior(Actor* owner, float weight, std::vector<Pathfinding::Node*> path) : m_path(path), Behavior(owner, weight, MathLibrary::Vector2(0, 0))
{
    if (!path.empty())
        setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
}

void PathBehavior::update(float deltaTime)
{
	if (!getWeight())
		return;

    Actor* owner = getOwner();
    MathLibrary::Vector2 ownerPosition = owner->getTransform()->getWorldPosition();
    MathLibrary::Vector2 ownerVelocity = owner->getVelocity();

    float distance = (getTargetPosition() - (ownerPosition + ownerVelocity)).getMagnitude();

    // if distance is less than that, pop off the front node and set the target position to the new front node (if there is one)
    if (distance < 20.0f && !m_path.empty())
    {
        // std::vector doesnt have a popFront function so we gotta do what we gotta do
        m_path.erase(m_path.begin());

        if (!m_path.empty())
            setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
    }

    // this is just slightly tweaked arrival
    MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerPosition) * owner->getMaxVelocity();

    if (distance < 80)
        desiredDirection = desiredDirection.getNormalized() * owner->getMaxVelocity() * (distance / (owner->getMaxVelocity() * 2.0f));

    MathLibrary::Vector2 steeringForce = desiredDirection - ownerVelocity;


    owner->setVelocity(ownerVelocity + (steeringForce * getWeight()) * deltaTime);
}

void PathBehavior::setPath(std::vector<Pathfinding::Node*> path)
{
    m_path = path;
    setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
}

bool PathBehavior::isPathEmpty()
{
   return m_path.empty();
}
