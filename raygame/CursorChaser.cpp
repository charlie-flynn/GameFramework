#include "CursorChaser.h"
#include "raylib.h"
#include "Transform2D.h"

CursorChaser::CursorChaser() : m_arrival(new Arrival(this, 1.0f, { 200, 200 }))
{
	setMaxVelocity(200.0f);
}

CursorChaser::CursorChaser(float x, float y) : Agent(x, y), m_arrival(new Arrival(this, 1.0f, {200, 200}))
{
	setMaxVelocity(200.0f);
}

void CursorChaser::start()
{
	addComponent(m_arrival);
}

void CursorChaser::update(float deltaTime)
{
	m_arrival->setTargetPosition(MathLibrary::Vector2(GetMouseX(), GetMouseY()));
	Agent::update(deltaTime);
}

void CursorChaser::draw()
{
	DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().y }, 3, 10, (-(getTransform()->getRotation()) * (180 / PI)) + 18, RED);
}
