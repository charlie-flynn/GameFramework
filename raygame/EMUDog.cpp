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
	m_lifeSpan(30.0f),
	m_target(nullptr),
	m_hasHat(false)
{
}

void EMUDog::start()
{
	Agent::start();

	// one in ten EMU dogs has a fun hat the makes them slightly smarter
	setCollider(new CircleCollider(150.0f, this));
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
	// make sure target isnt deleted
	BlackboardData* deletedActorData = Engine::getCurrentScene()->getBlackboard()->getData((char*)"ActorDeleted!");

	if (deletedActorData && m_target && deletedActorData->dataType == DATA_ACTORPOINTER && m_target == deletedActorData->actorData)
	{
		m_target = nullptr;
		setSeekTarget(nullptr);
	}

	Agent::update(deltaTime);

	// try to add itself to investigate queue if it hasnt already
	if (!m_blackboardNoticePosted)
	{
		if (Engine::getCurrentScene()->getBlackboard()->addData((char*)"AddToInvestigateQueue", new BlackboardData(this)))
			m_blackboardNoticePosted = true;
	}

	m_lifeSpan -= deltaTime;

	if (m_lifeSpan <= 0)
	{
		Engine::destroy(this);
		Engine::getCurrentScene()->getBlackboard()->replaceOrAddData((char*)"ActorDeleted!", new BlackboardData(this));
	}

	// i wanted to make this a component but it didn't work for no reason
	// so i'm hard coding this in. sorry !! ^^'  i really really hate this too

	MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();
	float screenWidth = (float)GetScreenWidth();
	float screenHeight = (float)GetScreenHeight();

	if (worldPosition.x < 0)
	{
		getTransform()->setWorldPosition({ 0, worldPosition.y });
	}
	if (worldPosition.x > screenWidth)
	{
		getTransform()->setWorldPosition({ screenWidth, worldPosition.y });
	}
	if (worldPosition.y < 0)
	{
		getTransform()->setWorldPosition({ worldPosition.x, 0 });
	}
	if (worldPosition.y > screenHeight)
	{
		getTransform()->setWorldPosition({ worldPosition.x, screenHeight });
	}
}

void EMUDog::draw()
{
	m_sprite->draw();

	if (m_hasHat)
	{
		MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();
		DrawRectangle(worldPosition.x - 5, worldPosition.y - 40, 20, 30, BLUE);
	}
}

void EMUDog::onCollision(Actor* collidedActor)
{
	// if its very big collider has hit an actor of ID 1 (alien), chase it until it dies badly
	if (collidedActor->getID() == 1 && !m_target)
	{
		m_target = collidedActor;
		setSeekTarget(m_target);
		setSeekWeight(1.0f);
		m_wander->setWeight(0.0f);
		setMaxVelocity(270.0f);
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
