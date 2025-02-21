#include "CursorChaser.h"
#include "raylib.h"
#include "Transform2D.h"

CursorChaser::CursorChaser() : m_seek(new Seek(this, 1.0f, { 200, 200 }))
{
	setMaxVelocity(100.0f);
}

CursorChaser::CursorChaser(float x, float y) : Agent(x, y), m_seek(new Seek(this, 1.0f, {200, 200}))
{
	setMaxVelocity(100.0f);
}

void CursorChaser::start()
{
	addComponent(m_seek);
}

void CursorChaser::update(float deltaTime)
{
	m_seek->setTargetPosition(MathLibrary::Vector2(GetMouseX(), GetMouseY()));
	Agent::update(deltaTime);
}

void CursorChaser::draw()
{
	DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().y }, 3, 10, (-(getTransform()->getRotation()) * (180 / PI)) + 18, RED);
}
