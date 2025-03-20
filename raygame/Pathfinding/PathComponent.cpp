#include "PathComponent.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"

PathComponent::PathComponent(Actor* owner, float speed, std::vector<Pathfinding::Node*> path) : m_path(path), m_speed(speed), Component(owner)
{
}

void PathComponent::update(float deltaTime)
{
    if (m_path.empty() || !getEnabled())
        return;

    MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();
    MathLibrary::Vector2 nodePosition = MathLibrary::Vector2(m_path.front()->position.x, m_path.front()->position.y);


    float distance = (nodePosition - ownerPosition).getMagnitude();

    if (distance > 0.1f)
    {
        MathLibrary::Vector2 towardsNode = (nodePosition - ownerPosition).getNormalized();
        towardsNode = towardsNode * m_speed;

        getOwner()->getTransform()->setWorldPosition(ownerPosition + towardsNode * deltaTime);
    }
    else
    {
        getOwner()->getTransform()->setWorldPosition(nodePosition);

        m_path.erase(m_path.begin());
    }


    /*
    if (m_path.empty()) return;


    // find out how far we have to go to the next node
    float dx = m_currentNode->position.x - ownerPosition.x;
    float dy = m_currentNode->position.y - ownerPosition.y;
    float distanceToNext = sqrtf(dx * dx + dy * dy);

    // normalize the vector to the next node
    if (distanceToNext > 0)
    {
        dx /= distanceToNext;
        dy /= distanceToNext;
    }

    distanceToNext -= m_speed * deltaTime;
    if (distanceToNext >= 0)
    {
        // we wont get to the target node this frame - so move linearly towards it
        position.x += dx * speed * deltaTime;
        position.y += dy * speed * deltaTime;
    }
    else
    {
        currentIndex++;
        if (currentIndex >= m_path.size())
        {
            // we've reached the end, so stop on the node and clear our m_path
            position.x = m_currentNode->position.x;
            position.y = m_currentNode->position.y;
            m_path.clear();
        }
        else
        {
            // move on to the next node
            Pathfinding::Node* oldNode = m_currentNode;
            m_currentNode = m_path[currentIndex];

            // get the unit vectore from the old node to the new one
            dx = m_currentNode->position.x - oldNode->position.x;
            dy = m_currentNode->position.y - oldNode->position.y;
            float mag = sqrtf(dx * dx + dy * dy);
            dx /= mag;
            dy /= mag;

            // move along the path from the previous node to the new current node by the amount by which we overshot
            // (which is -distanceToNext)
            ownerPosition.x = oldNode->position.x - distanceToNext * dx;
            ownerPosition.y = oldNode->position.y - distanceToNext * dy;
        }
    }
    */
}
