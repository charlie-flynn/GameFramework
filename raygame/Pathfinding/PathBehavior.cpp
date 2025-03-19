#include "PathBehavior.h"
#include "Actor.h"
#include "Transform2D.h"

#include <iostream>
PathBehavior::PathBehavior(Actor* owner, float weight, std::vector<Pathfinding::Node*> path) : m_path(path), Behavior(owner, weight, MathLibrary::Vector2(0, 0))
{
    if (!path.empty())
        setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
}

void PathBehavior::update(float deltaTime)
{
	if (!getWeight() || m_path.empty())
		return;

    Actor* owner = getOwner();
    MathLibrary::Vector2 ownerPosition = owner->getTransform()->getWorldPosition();
    MathLibrary::Vector2 ownerVelocity = owner->getVelocity();

    float distance = (getTargetPosition() - ownerPosition).getMagnitude();

    if (distance < 15.0f)
    {
        // std::vector doesnt have a popFront function so we gotta do what we gotta do
        m_path.erase(m_path.begin());

        // set target position to the next node (if there is one)
        if (m_path.size())
            setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
    }

    MathLibrary::Vector2 desiredDirection = MathLibrary::Vector2::normalize(getTargetPosition() - ownerPosition) * owner->getMaxVelocity();

    // if only one node, decelerate rapidly
    if (distance < owner->getMaxVelocity())
        desiredDirection = desiredDirection.getNormalized() * owner->getMaxVelocity() * (distance / (owner->getMaxVelocity() * 1.2f));

    MathLibrary::Vector2 steeringForce = desiredDirection - ownerVelocity;


    owner->setVelocity(ownerVelocity + (steeringForce * getWeight()) * deltaTime);

	/*
	* if (path.empty()) return;

        // find out how far we have to go to the next node
        float dx = currentNode->position.x - position.x;
        float dy = currentNode->position.y - position.y;
        float distanceToNext = sqrtf(dx * dx + dy * dy);

        // normalize the vector to the next node
        if (distanceToNext > 0)
        {
            dx /= distanceToNext;
            dy /= distanceToNext;
        }

        distanceToNext -= speed * deltaTime;
        if (distanceToNext >= 0)
        {
            // we wont get to the target node this frame - so move linearly towards it
            position.x += dx * speed * deltaTime;
            position.y += dy * speed * deltaTime;
        }
        else
        {
            currentIndex++;
            if (currentIndex >= path.size())
            {
                // we've reached the end, so stop on the node and clear our path
                position.x = currentNode->position.x;
                position.y = currentNode->position.y;
                path.clear();
            }
            else
            {
                // move on to the next node
                Node* oldNode = currentNode;
                currentNode = path[currentIndex];

                // get the unit vectore from the old node to the new one
                dx = currentNode->position.x - oldNode->position.x;
                dy = currentNode->position.y - oldNode->position.y;
                float mag = sqrtf(dx * dx + dy * dy);
                dx /= mag;
                dy /= mag;

                // move along the path from the previous node to the new current node by the amount by which we overshot
                // (which is -distanceToNext)
                position.x = oldNode->position.x - distanceToNext * dx;
                position.y = oldNode->position.y - distanceToNext * dy;
            }
        }
	*/
}

void PathBehavior::setPath(std::vector<Pathfinding::Node*> path)
{
    m_path = path;
    setTargetPosition(m_path.front()->position.x, m_path.front()->position.y);
}
