#include "Alien.h"
#include "Transform2D.h"
#include <random>

Alien::Alien()
{
}

Alien::Alien(float x, float y) :
	m_pathBehavior(new PathBehavior(this, 0.0f, nullptr)),
	m_arrival(new Arrival(this, 0.0f, {0, 0})),
	m_flee(new Flee(this, 0.0f, {0, 0})),
	m_evade(new Evade(this, 0.0f, nullptr)),
	m_seek(new Seek(this, 0.0f, {0, 0})),
	m_pursue(new Pursue(this, 0.0f, nullptr)),
	m_isSmarter(false),
	m_state(WANDER_STATE),
	m_nodeMap(nullptr),
	m_target(nullptr)
{
	getTransform()->setWorldPosition(MathLibrary::Vector2(x, y));
	getTransform()->setScale(MathLibrary::Vector2(50, 50));
}

Alien::Alien(Pathfinding::NodeMap nodeMap, float x, float y) :
	m_pathBehavior(new PathBehavior(this, 0.0f, nullptr)),
	m_arrival(new Arrival(this, 0.0f, { 0, 0 })),
	m_flee(new Flee(this, 0.0f, { 0, 0 })),
	m_evade(new Evade(this, 0.0f, nullptr)),
	m_seek(new Seek(this, 0.0f, { 0, 0 })),
	m_pursue(new Pursue(this, 0.0f, nullptr)),
	m_isSmarter(false),
	m_state(WANDER_STATE),
	m_nodeMap(nullptr),
	m_target(nullptr)
{
	getTransform()->setWorldPosition(MathLibrary::Vector2(x, y));
	getTransform()->setScale(MathLibrary::Vector2(50, 50));
}

void Alien::start()
{
	Agent::start();

	if (std::rand() % 10000 == 0)
	{
		m_sprite = new SpriteComponent(this, "Images/rainbow alien RARE.png");
		m_isSmarter = true;
	}
	else
	{
		int rand = std::rand() % 5;
		switch (rand)
		{
		case 0:
			m_sprite = new SpriteComponent(this, "Images/blue alien.png");
			m_isSmarter = false;
			break;
		case 1:
			m_sprite = new SpriteComponent(this, "Images/purple alien.png");
			m_isSmarter = false;
			break;
		case 2:
			m_sprite = new SpriteComponent(this, "Images/pink alien.png");
			m_isSmarter = true;
			break;
		case 3:
			m_sprite = new SpriteComponent(this, "Images/burgundy alien.png");
			m_isSmarter = true;
			break;
		case 4:
			m_sprite = new SpriteComponent(this, "Images/blue alien.png");
			m_isSmarter = true;
			break;
		}
	}



	addComponent(m_sprite);
}

void Alien::update(float deltaTime)
{
	Agent::update(deltaTime);
	m_sprite->draw();
}

void Alien::wanderUpdate()
{
}

void Alien::investigateUpdate()
{
}

void Alien::eatTargetUpdate()
{
}

void Alien::blastTargetUpdate()
{
}

void Alien::fleeTargetUpdate()
{
}

void Alien::onEnterInvestigate()
{
}
