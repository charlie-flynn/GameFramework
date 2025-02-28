#include "Hunter.h"

#include "Wander.h"
#include "Pursue.h"
#include "Seek.h"

#include "raylib.h"

#include "Transform2D.h"

Hunter::Hunter()
{
}

Hunter::Hunter(float x, float y, Actor* target) : Agent(x, y), 
m_target(target),
m_state(STATE_FIND),
m_wander(new Wander(this, 0.6f, 80.0f, 40.0f)),
m_pursue(new Pursue(this, 0.0f, target)),
m_seek(new Seek(this, 0.3f, target))
{
	setMaxVelocity(150.0f);
}

Hunter::~Hunter()
{
	delete m_wander;

	delete m_seek;
}

void Hunter::start()
{
	Agent::start();
	addComponent(m_wander);
	addComponent(m_pursue);
	addComponent(m_seek);
}

void Hunter::update(float deltaTime)
{
	Agent::update(deltaTime);

	float distanceToTarget;
	
	if (m_target)
		distanceToTarget = (getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).getMagnitude();
	else
		distanceToTarget = 9999;

	switch (m_state)
	{
	case STATE_FIND:
		if (distanceToTarget < 200)
			setState(STATE_STALK);
		break;
	case STATE_STALK:
		if (distanceToTarget > 250)
			setState(STATE_FIND);
		else if (distanceToTarget < 100)
			setState(STATE_PURSUE);
		break;
	case STATE_PURSUE:
		if (distanceToTarget > 250)
			setState(STATE_FIND);
		break;
	default:
		break;
	}
}

void Hunter::draw()
{
	MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();

	Color color;
	Vector2 position = { worldPosition.x, worldPosition.y };

	switch (m_state)
	{
	case STATE_FIND:
		color.a = 255;
		color.r = 10;
		color.g = 125;
		color.b = 40;
		break;
	case STATE_STALK:
		color.a = 125;
		color.r = 10;
		color.g = 125;
		color.b = 40;
		break;
	case STATE_PURSUE:
		color.a = 255;
		color.r = 30;
		color.g = 200;
		color.b = 60;
		break;
	default:
		color.a = 255;
		color.r = 255;
		color.g = 0;
		color.b = 0;
		break;
	}

	DrawPoly(position, 3, 20, -getTransform()->getRotation() * (180 / PI) + 18, color);
}

void Hunter::setState(int state)
{
	m_state = state;

	switch (m_state)
	{
	case STATE_FIND:
		m_wander->setWeight(0.6f);
		m_pursue->setWeight(0.0f);
		m_seek->setWeight(0.3f);

		setMaxVelocity(150.0f);
		break;
	case STATE_STALK:
		m_wander->setWeight(0.0f);
		m_pursue->setWeight(0.0f);
		m_seek->setWeight(1.0f);

		setMaxVelocity(50.0f);
		break;
	case STATE_PURSUE:
		m_wander->setWeight(0.0f);
		m_pursue->setWeight(1.0f);
		m_seek->setWeight(0.0f);

		setMaxVelocity(300.0f);
		break;
	default:
		break;
	}
}
