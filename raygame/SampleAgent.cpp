#include "SampleAgent.h"
#include "raylib.h"
#include "Transform2D.h"


SampleAgent::SampleAgent(float x, float y) : Agent(x, y), m_seek(new Seek(this, 0.0f, {200, 200})), m_flee(new Flee(this, 0.0f, {200, 200})), m_wander(new Wander(this, 1.0f, 20.0f, 20.0f))
{
}

void SampleAgent::start()
{
	addComponent<Seek>(m_seek);
	addComponent<Flee>(m_flee);
	addComponent<Wander>(m_wander);
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
