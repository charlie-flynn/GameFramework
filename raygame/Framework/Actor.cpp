#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"
#include "Vector3.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
    m_maxVelocity = 200.0f;
    m_started = false;
    m_components = DynamicArray<Component*>();
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, int ID = 0)
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_id = ID;
    m_maxVelocity = 200.0f;
    m_started = false;
    m_components = DynamicArray<Component*>();
}

Component* Actor::addComponent(Component* component)
{
    if (component->getOwner() != this)
        return nullptr;

    m_components.Add(component);

    return component;
}

void Actor::start()
{
    m_started = true;

    m_transform->updateTransforms();

    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->start();
    }
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->onCollision(other);
    }
}

void Actor::setVelocity(MathLibrary::Vector2 value)
{
    m_velocity = value;

    if (m_velocity.getMagnitude() > m_maxVelocity)
        m_velocity = m_velocity.getNormalized() * m_maxVelocity;

    /*
    if (value.x > 0)
        m_velocity.x = std::fmin(value.x, m_maxVelocity);
    else
        m_velocity.x = std::fmax(value.x, -m_maxVelocity);

    if (value.y > 0)
        m_velocity.y = std::fmin(value.y, m_maxVelocity);
    else
        m_velocity.y = std::fmax(value.y, -m_maxVelocity);
    */
}

void Actor::setVelocity(float x, float y)
{
    m_velocity.x = x;
    m_velocity.y = y;

    if (m_velocity.getMagnitude() > m_maxVelocity)
        m_velocity = m_velocity.getNormalized() * m_maxVelocity;

    /*
    if (x > 0)
        m_velocity.x = std::fmin(x, m_maxVelocity);
    else
        m_velocity.x = std::fmax(x, -m_maxVelocity);

    if (y > 0)
        m_velocity.y = std::fmin(y, m_maxVelocity);
    else
        m_velocity.y = std::fmax(y, -m_maxVelocity);
    */
}

void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();

    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->update(deltaTime);
    }
}

void Actor::draw()
{
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->draw();
    }
}

void Actor::end()
{
    m_started = false;
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->end();
    }
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());

    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->onDestroy();
    }
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}