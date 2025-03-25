#include "Walterberry.h"
#include "raylib.h"
#include "Engine.h"
#include "Scene.h"
#include "CircleCollider.h"
#include "Transform2D.h"

Walterberry::Walterberry(float x, float y) : Actor(x, y, 2), m_sprite(new SpriteComponent(this, "Images/walterberry.png")), m_blackboardNoticePosted(false)
{
	getTransform()->setScale({ 50, 50 });
	setCollider(new CircleCollider(20.0f, this));
}

Walterberry::~Walterberry()
{
	Actor::~Actor();
	delete m_sprite;
	m_sprite = nullptr;
}

void Walterberry::update(float deltaTime)
{
	Actor::update(deltaTime);

	// try to post a blackboard notice to get added to the queue
	if (!m_blackboardNoticePosted)
	{
		if (Engine::getCurrentScene()->getBlackboard()->addData((char*)"AddToInvestigateQueue", new BlackboardData(this)))
			m_blackboardNoticePosted = true;
	}
}

void Walterberry::draw()
{
	Actor::draw();

	m_sprite->draw();
}

void Walterberry::onCollision(Actor* collidedActor)
{
	// if it collided with an actor of ID 1 (alien), destroy it
	if (collidedActor->getID() == 1)
	{
		Engine::getCurrentScene()->getBlackboard()->removeData((char*)"AlienCanInvestigate");
		Engine::destroy(this);
		Engine::getCurrentScene()->getBlackboard()->replaceOrAddData((char*)"ActorDeleted!", new BlackboardData(this));
	}
}
