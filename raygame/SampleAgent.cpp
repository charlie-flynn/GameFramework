#include "SampleAgent.h"
#include "raylib.h"
#include "Transform2D.h"


SampleAgent::SampleAgent(float x, float y) : Agent(x, y), m_behavior(new Seek(this, 1.0f, {200, 200}))
{
}

void SampleAgent::start()
{
	addComponent<Seek>(m_behavior);
}

void SampleAgent::update(float deltaTime)
{
	m_behavior->setTargetPosition(MathLibrary::Vector2(GetMouseX(), GetMouseY()));
	Agent::update(deltaTime);
}

void SampleAgent::draw()
{
	DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().y }, 3, 20, (-(getTransform()->getRotation()) * (180 / PI)) + 18, GREEN);
}
