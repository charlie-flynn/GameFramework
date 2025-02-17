#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

/*
Component* Actor::getComponent(const char* componentName)
{
    //Iterate through all of the components in the array.
    for (int i = 0; i < m_components.Length(); i++)
    {
        //If the component name matches the name given...
        if (m_components[i]->getName() == componentName)
        {
            //...return the component.
            return m_components[i];
        }
    }

    //Return null by default.
    return nullptr;
}
*/

/*
*/
Component* Actor::addComponent(Component* component)
{
    //If this actor doesn't own this component...
    Actor* owner = component->getOwner();
    if (owner && owner != this)
    {
        //...return nullptr to prevent it from being added.
        return nullptr;
    }

    m_components.PushBack(component);

    return component;

    /*
    //Create a new array that has a size that is greater than the original by one.
    Component** tempArray = new Component * [m_components.Length() + 1];

    //Copy all values from the old array to the temp array.
    for (int i = 0; i < m_components.Length(); i++)
    {
        tempArray[i] = m_components[i];
    }

    //Delete the old array.
    delete m_components;

    //Set the last index in the temp array to be the component we want to add.
    tempArray[m_components.Length()] = component;

    //Set the original array to be the temp array.
    m_components = tempArray;
    //Increment the component count.
    m_components.Length()++;

    //Return the new component that was added.
    return component;
    */

}

Component* Actor::addBehavior(Component* behavior)
{
    //If this actor doesn't own this component...
    Actor* owner = behavior->getOwner();
    if (owner && owner != this)
    {
        //...return nullptr to prevent it from being added.
        return nullptr;
    }

    m_components.PushFront(behavior);
    behaviorCount++;

    return behavior;
}

/*
bool Actor::removeComponent(const char* componentName)
{
    //If the component name is null..
    if (!componentName)
    {
        //...return false.
        return false;
    }

    //Create a new variable to store whether or not the component was removed.
    bool componentRemoved = false;

    //Create a new temporary array to copy the values over to.
    Component** tempArray = new Component * [m_components.Length() - 1];

    //Copy all values except for the one to remove.
    int j = 0;
    for (int i = 0; i < m_components.Length(); i++)
    {
        //If this component doesn't match the name given...
        if (componentName != m_components[i]->getName())
        {
            //...copy the value from the original to the temp array.
            tempArray[j] = m_components[i];
            j++;
        }
        //Otherwise...
        else
        {
            //...mark that the component was removed.
            componentRemoved = true;
        }
    }

    //If the component was removed...
    if (componentRemoved)
    {
        //...delete the old array and set it to the new array.
        delete m_components;
        m_components = tempArray;
        m_components.Length()--;
    }
    //Otherwise...
    else
    {
        //...delete the new array.
        delete[] tempArray;
    }

    return componentRemoved;
}
*/

void Actor::start()
{
    m_started = true;

    Iterator<Component*> iter = m_components.begin();
    while ((*iter) != nullptr)
    {
        (*iter)->start();
        iter++;
    }
}

void Actor::onCollision(Actor* other)
{
    Iterator<Component*> iter = m_components.begin();
    while ((*iter) != nullptr)
    {
        (*iter)->onCollision(other);
        iter++;
    }
}

void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();

    
    Iterator<Component*> iter = m_components.begin();
    while ((*iter) != nullptr)
    {
        (*iter)->update(deltaTime);
        iter++;
    }
}

void Actor::draw()
{
    Iterator<Component*> iter = m_components.begin();
    while ((*iter) != nullptr)
    {
        (*iter)->draw();
        iter++;
    } 
}

void Actor::end()
{
    Iterator<Component*> iter = m_components.begin();
    while ((*iter) != nullptr)
    {
        (*iter)->end();
        iter++;
    }
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());

    for (Iterator<Component*> iter = m_components.begin(); ++iter != nullptr; iter++)
    {
        (*iter)->onDestroy();
    }
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}