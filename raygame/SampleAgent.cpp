#include "SampleAgent.h"
#include "raylib.h"
#include "Transform2D.h"




SampleAgent::SampleAgent(float x, float y) : Agent(x, y), m_seek(new Seek(this, 0.0f, {200, 200})), 
m_flee(new Flee(this, 0.0f, {200, 200})), 
m_wander(new Wander(this, 0.0f, 50.0f, 30.0f)),
m_pathBehavior(new PathBehavior(this, 1.0f, new std::vector<Pathfinding::Node*>()))
{
	setMaxVelocity(100.0f);
}

void SampleAgent::start()
{
	addComponent(m_seek);
	addComponent(m_flee);
	addComponent(m_wander);
	addComponent(m_pathBehavior);

	Agent::start();
}

void SampleAgent::update(float deltaTime)
{
	m_seek->setTargetPosition(MathLibrary::Vector2(GetMouseX(), GetMouseY()));
	m_flee->setTargetPosition(MathLibrary::Vector2(GetMouseX(), GetMouseY()));
	Agent::update(deltaTime);
}

void SampleAgent::draw()
{
	DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().y }, 3, 20, (-(getTransform()->getRotation()) * (180 / PI)) + 18, GREEN);
}
