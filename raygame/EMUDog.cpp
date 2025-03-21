#include "EMUDog.h"
#include "Wander.h"
#include "Seek.h"
#include "Pursue.h"
#include <random>
#include "Transform2D.h"
#include "Collider.h"
#include "Engine.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "raylib.h"
#include "CircleCollider.h"

EMUDog::EMUDog()
{
}

EMUDog::EMUDog(float x, float y) : 
	Agent(x, y, 3),
	m_wander(new Wander(this, 1.0f, 50, 130)),
	m_seek(new Seek(this, 0.0f, {0, 0})),
	m_pursue(new Pursue(this, 0.0f, nullptr)),
	m_sprite(new SpriteComponent(this, "Images/EMU dog.png")),
	m_lifeSpan(5.0f),
	m_target(nullptr),
	m_hasHat(false)
{
}

void EMUDog::start()
{
	Agent::start();

	setCollider(new CircleCollider(30.0f, this));
	int rng = std::rand() % 10;

	m_hasHat = rng == 0;

	addBehavior(m_wander);

	if (m_hasHat)
	{
		delete m_seek;
		m_seek = nullptr;
		addBehavior(m_pursue);
	}
	else
	{
		delete m_pursue;
		m_pursue = nullptr;
		addBehavior(m_seek);
	}

	setMaxVelocity(100.0f);

	m_sprite->setTextureRotating(false);
	addComponent(m_sprite);

	getTransform()->setScale({50, 50});
}

void EMUDog::update(float deltaTime)
{
	Agent::update(deltaTime);

	if (!m_blackboardNoticePosted)
	{
		if (Engine::getCurrentScene()->getBlackboard()->addData((char*)"AlienCanInvestigate", new BlackboardData(this)))
			m_blackboardNoticePosted = true;
	}

	m_lifeSpan -= deltaTime;

	if (m_lifeSpan <= 0)
	{
		Engine::destroy(this);
		Engine::getCurrentScene()->getBlackboard()->replaceOrAddData((char*)"ActorDeleted!", new BlackboardData(this));
	}


}

void EMUDog::draw()
{
	m_sprite->draw();

	if (m_hasHat)
	{
		MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();
		DrawRectangle(worldPosition.x, worldPosition.y - 40, 20, 30, BLUE);
	}
}

void EMUDog::onCollision(Actor* collidedActor)
{
	if (collidedActor->getID() == 1 && !m_target)
	{
		m_target = collidedActor;
		setSeekTarget(m_target);
		setSeekWeight(1.0f);
		m_wander->setWeight(0.0f);
		setMaxVelocity(210.0f);
	}
}

void EMUDog::setSeekTarget(Actor* target)
{
	if (m_hasHat)
		m_pursue->setTargetActor(target);
	else
		m_seek->setTargetActor(target);
}

void EMUDog::setSeekWeight(float weight)
{
	if (m_hasHat)
		m_pursue->setWeight(weight);
	else
		m_seek->setWeight(weight);
}
