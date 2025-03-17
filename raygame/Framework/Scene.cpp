#include "Scene.h"
#include "Transform2D.h"
#include "DynamicArray.h"

Scene::Scene()
{
    m_actorCount = 0;
    m_actors = DynamicArray<Actor*>();
    m_world = new MathLibrary::Matrix3();
}

MathLibrary::Matrix3* Scene::getWorld()
{
    return m_world;
}

void Scene::addUIElement(Actor* actor)
{
    m_UIElements.Add(actor);

    //Adds all children of the UI to the scene
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_UIElements.Add(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

void Scene::removeUIElement(int index)
{
    m_UIElements.RemoveIndex(index);
}

void Scene::removeUIElement(Actor* actor)
{
    m_UIElements.Remove(actor);
}

void Scene::addActor(Actor* actor)
{
    m_actors.Add(actor);

    //Adds all children of the actor to the scene
    for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
    {
        m_actors.Add(actor->getTransform()->getChildren()[i]->getOwner());
    }
}

void Scene::removeActor(int index)
{
    m_actors.RemoveIndex(index);
}

void Scene::removeActor(Actor* actor)
{
    m_actors.Remove(actor);
}

void Scene::start()
{
    m_started = true;
}

void Scene::update(float deltaTime)
{
    //Updates all actors
    for (int i = 0; i < m_actors.Length(); i++)
    {
        if (!m_actors[i]->getStarted())
            m_actors[i]->start();

        m_actors[i]->update(deltaTime);
    }

    //Checks collision for all actors
    for (int i = 0; i < m_actors.Length(); i++)
    {
        for (int j = 0; j < m_actors.Length(); j++)
        {
            if (m_actors[i]->checkForCollision(m_actors[j]) && j != i && m_actors[j]->getStarted())
                m_actors[i]->onCollision(m_actors[j]);
        }
    }
}

void Scene::updateUI(float deltaTime)
{
    //Calls update for all actors in UI array
    for (int i = 0; i < m_UIElements.Length(); i++)
    {
        if (!m_UIElements[i]->getStarted())
            m_UIElements[i]->start();

        m_UIElements[i]->update(deltaTime);
    }
}

void Scene::draw()
{
    //Calls draw for all actors in the array
    for (int i = 0; i < m_actors.Length(); i++)
    {
        m_actors[i]->draw();
    }
}

void Scene::drawUI()
{
    //Calls draw for all actors in UI array
    for (int i = 0; i < m_UIElements.Length(); i++)
    {
        m_UIElements[i]->draw();
    }
}

void Scene::end()
{
    //Calls end for all actors in the array
    for (int i = 0; i < m_actors.Length(); i++)
    {
        if (m_actors[i]->getStarted())
            m_actors[i]->end();
    }

    m_started = false;
}