#include "Alien.h"
#include "Transform2D.h"
#include <random>

#include "Engine.h"
#include "Scene.h"

#include "CircleCollider.h"

Alien::Alien()
{
}

Alien::Alien(float x, float y) :
	m_pathComponent(new PathComponent(this, 150.0f, std::vector<Pathfinding::Node*>())),
	m_arrival(new Arrival(this, 0.0f, { 0, 0 })),
	m_flee(new Flee(this, 0.0f, { 0, 0 })),
	m_evade(new Evade(this, 0.0f, nullptr)),
	m_seek(new Seek(this, 0.0f, { 0, 0 })),
	m_pursue(new Pursue(this, 0.0f, nullptr)),
	m_isSmarter(false),
	m_state(WANDER_STATE),
	m_nodeMap(nullptr),
	m_target(nullptr),
	m_isDead(false),
	m_health(10),
	m_maxHealth(10)
{
	if (std::rand() % 4096 == 0)
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
			m_sprite = new SpriteComponent(this, "Images/yellow alien.png");
			m_isSmarter = true;
			break;
		}
	}
}

Alien::Alien(Pathfinding::NodeMap* nodeMap, float x, float y) :
	Agent(x, y, 1),
	m_pathComponent(new PathComponent(this, 150.0f, std::vector<Pathfinding::Node*>())),
	m_arrival(new Arrival(this, 0.0f, { 0, 0 })),
	m_flee(new Flee(this, 0.0f, { 0, 0 })),
	m_evade(new Evade(this, 0.0f, nullptr)),
	m_seek(new Seek(this, 0.0f, { 0, 0 })),
	m_pursue(new Pursue(this, 0.0f, nullptr)),
	m_isSmarter(false),
	m_state(WANDER_STATE),
	m_nodeMap(nodeMap),
	m_target(nullptr),
	m_isDead(false),
	m_health(10),
	m_maxHealth(10)
{
	if (std::rand() % 4096 == 0)
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
			m_sprite = new SpriteComponent(this, "Images/yellow alien.png");
			m_isSmarter = true;
			break;
		}
	}
}

Alien::~Alien()
{
	Actor::~Actor();

	delete m_pathComponent;
	m_pathComponent = nullptr;
	delete m_arrival;
	m_arrival = nullptr;

	delete m_seek;
	m_seek = nullptr;

	if (m_flee)
		delete m_flee;
	m_flee = nullptr;

	if (m_evade)
		delete m_evade;
	m_evade = nullptr;

	if (m_pursue)
		delete m_pursue;
	m_pursue = nullptr;

	delete m_sprite;
	m_sprite = nullptr;
}

void Alien::start()
{
	Agent::start();

	

	int scaleVarianceX = ((std::rand() % 20) + 1) - 10;
	int scaleVarianceY = ((std::rand() % 20) + 1) - 10;

	if (std::rand() % 500 == 0)
	{
		scaleVarianceX *= 10;
		scaleVarianceY *= 10;
	}

	getTransform()->setScale(MathLibrary::Vector2(50 + scaleVarianceX, 50 + scaleVarianceY));

	setCollider(new CircleCollider(10, this));

	m_sprite->setTextureRotating(false);
	m_sprite->setYOffset(-20.0f);
	addComponent(m_sprite);


	m_pathComponent->setEnabled(true);
	setMaxVelocity(200.0f);

	setState(WANDER_STATE);

	addComponent(m_pathComponent);

	// add all the behaviors
	addBehavior(m_arrival);
	addBehavior(m_seek);

	// delete the ones we're not using
	if (m_isSmarter)
	{
		delete m_flee;
		m_flee = nullptr;
		// we cant delete seek because
		// we're using it in wanderUpdate

		addBehavior(m_pursue);
		addBehavior(m_evade);
	}
	else
	{
		delete m_pursue;
		m_pursue = nullptr;
		delete m_evade;
		m_evade = nullptr;

		addBehavior(m_flee);
	}
}

void Alien::update(float deltaTime)
{

	// check if the current target has been deleted every frame via checking the blackboard for notices
	// if it has, set target to nullptr
	BlackboardData* deletedActorData = Engine::getCurrentScene()->getBlackboard()->getData((char*)"ActorDeleted!");

	if (deletedActorData && m_target && deletedActorData->dataType == DATA_ACTORPOINTER && m_target == deletedActorData->actorData)
	{
		m_target = nullptr;
		setSeekTarget(nullptr);
		setFleeTarget(nullptr);
	}

	if (m_invincibilityFramesTimer > 0)
		m_invincibilityFramesTimer -= deltaTime;

	if (m_isDead)
	{
		Engine::getCurrentScene()->getBlackboard()->replaceOrAddData((char*)"ActorDeleted!", new BlackboardData(this));
		Engine::destroy(this);
	}

	Agent::update(deltaTime);
	// finite state machine
	switch (m_state)
	{
	case WANDER_STATE:
		// wanders randomly around the path, navigating using A*
		// if something that can be investigated is kinda close,
		// switches to investigate state
		wanderUpdate();
		break;
	case INVESTIGATE_STATE:
		// arrives at a spot kinda close to the target
		// based on what the target does and if the alien
		// has a blaster, switches to any of the other three states
		// can also use blackboard memory to switch faster if it has seen
		// the target before
		investigateUpdate(deltaTime);
		break;
	case EAT_TARGET_STATE:
		// attempts to arrive (or pursue) the target to eat them
		// after succeeding or failing, switch back to wander
		eatTargetUpdate();
		break;
	case BLAST_TARGET_STATE:
		// attempts to run away from the target using flee or evade
		// and after reaching a certain distance, begin blasting the target
		// return to wander state after the target dies
		blastTargetUpdate(deltaTime);
		break;
	case FLEE_TARGET_STATE:
		// attempts to run away from the target using flee or evade
		// after reaching a certain distance, continue maintaining that distance
		// return to wander state after the target dies
		fleeTargetUpdate();
		break;
	default:
		// switch to wander state in case someone screws up the state machine somehow
		m_state = WANDER_STATE;
		wanderUpdate();
		break;
	}
}

void Alien::draw()
{
	m_sprite->draw();

	MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();

	Vector2 startPos = Vector2();
	Vector2 endPos = Vector2();

	startPos.x = worldPosition.x - 25;
	startPos.y = worldPosition.y - 80;

	endPos.x = (startPos.x) + ((50 * m_health) / m_maxHealth);
	endPos.y = worldPosition.y - 80;

	DrawLineEx(startPos, endPos, 4, RED);

	//getCollider()->draw();

	//MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();
	//DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().y }, 3, 20, (-(getTransform()->getRotation()) * (180 / PI)) + 18, GREEN);
}

void Alien::takeDamage(int damage, Actor* source)
{
	if (m_invincibilityFramesTimer > 0)
		return;

	m_invincibilityFramesTimer = 3.0f;

	m_health -= damage;

	if (m_health <= 0)
		m_isDead = true;
	else if (source)
	{
		BlackboardData* newData = new BlackboardData(source->getID());
		if (!getBlackboard()->addData((char*)"AGRESSIVE" + source->getID(), newData))
			delete newData;

		m_target = source;

		setState(FLEE_TARGET_STATE);
	}
}

void Alien::heal(int healing, Actor* source)
{
	m_health += healing;

	if (m_health >= m_maxHealth)
		m_health = m_maxHealth;
	if (source)
	{
		BlackboardData* newData = new BlackboardData(source->getID());
		if (!getBlackboard()->addData((char*)"YUMMY" + source->getID(), newData))
			delete newData;
	}
}

void Alien::wanderUpdate()
{
	BlackboardData* data = Engine::getCurrentScene()->getBlackboard()->getData((char*)"AlienCanInvestigate");

	if (data)
	{
		if (data->dataType == DATA_ACTORPOINTER)
		{
			Actor* actor = data->actorData;
			MathLibrary::Vector2 actorPosition = data->actorData->getTransform()->getWorldPosition();

			if ((getTransform()->getWorldPosition() - actorPosition).getMagnitude() < 150)
			{
				// get the vector pointing from the actor to the alien
				// and use it to get a position a slight distance away from the actor

				MathLibrary::Vector2 targetPosition = (getTransform()->getWorldPosition() - actorPosition).getNormalized();
				targetPosition = (targetPosition * 80) + actorPosition;

				m_arrival->setTargetPosition(targetPosition);

				m_target = actor;
				setSeekTarget(actor);

				setState(INVESTIGATE_STATE);
			}
		}
	}

	if (!m_nodeMap)
		return;

	// check if the current path is empty
	if (m_pathComponent->isPathEmpty())
	{
		// if so, check if there is a node nearby, and if so, create a new path to another random node
		// otherwise, seek to the center of the window
		if (m_nodeMap->GetClosestNode(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y) != nullptr)
		{
			m_seek->setWeight(0.0f);
			m_pathComponent->setEnabled(true);

			Pathfinding::Node* randomNode;

			do
			{
				int randomX = std::rand() % m_nodeMap->width;
				int randomY = std::rand() % m_nodeMap->height;
				randomNode = m_nodeMap->GetNode(randomX, randomY);
			} while (!randomNode);

			std::vector<Pathfinding::Node*> path = Pathfinding::AStarSearch(m_nodeMap->GetClosestNode(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y), randomNode);

			path = Pathfinding::GetSmoothedPath(path);

			m_pathComponent->setPath(path);
			setVelocity(0, 0);

		}
		else
		{
			m_seek->setTargetPosition(MathLibrary::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2));

			m_pathComponent->setEnabled(false);
			m_seek->setWeight(1.0f);
		}
	}
}

void Alien::investigateUpdate(float deltaTime)
{
	if (!m_target)
		setState(WANDER_STATE);

	m_investigateTimer -= deltaTime;

	// if the timer runs out and nothing bad happened, attempt to eat the target
	if (m_investigateTimer <= 0.0f)
	{
		setState(EAT_TARGET_STATE);
	}

	// if the timer is slightly less than timed out and there is memory, act accordingly
	if (m_investigateTimer <= 8.5f)
	{
		if (getBlackboard()->getData((char*)"AGRESSIVE" + m_target->getID()))
			setState(FLEE_TARGET_STATE);

		if (getBlackboard()->getData((char*)"YUMMY" + m_target->getID()))
			setState(EAT_TARGET_STATE);

	}
}

void Alien::eatTargetUpdate()
{
	if (!m_target)
		setState(WANDER_STATE);
}

void Alien::blastTargetUpdate(float deltaTime)
{
	if (!m_target)
		setState(WANDER_STATE);
}

void Alien::fleeTargetUpdate()
{
	if (!m_target)
		setState(WANDER_STATE);


}

void Alien::setState(EAlienStateMachine state)
{
	m_state = state;

	switch (m_state)
	{
	case WANDER_STATE:	
		setBehaviorWeights(true, 0.0f, 0.0f, 0.0f);
		setVelocity(0, 0);
		setMaxVelocity(200);
		break;
	case INVESTIGATE_STATE:
		setBehaviorWeights(false , 1.0f, 0.0f, 0.0f);
		m_investigateTimer = 10.0f;
		break;
	case EAT_TARGET_STATE:
		setMaxVelocity(100);
		setBehaviorWeights(false, 0.0f, 0.0f, 1.0f);
		break;
	case BLAST_TARGET_STATE:
		setBehaviorWeights(false, 0.0f, 1.0f, 0.0f);
		break;
	case FLEE_TARGET_STATE:
		setBehaviorWeights(false, 0.0f, 1.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Alien::setBehaviorWeights(bool pathEnabled, float arrivalWeight, float fleeWeight, float seekWeight)
{
	m_pathComponent->setEnabled(pathEnabled);
	m_arrival->setWeight(arrivalWeight);
	
	if (m_isSmarter)
	{
		m_evade->setWeight(fleeWeight);
		m_pursue->setWeight(seekWeight);
	}
	else
	{
		m_flee->setWeight(fleeWeight);
		m_seek->setWeight(seekWeight);
	}
}

void Alien::setSeekTarget(Actor* target)
{
	if (m_isSmarter)
		m_pursue->setTargetActor(target);
	else
		m_seek->setTargetActor(target);
}

void Alien::setFleeTarget(Actor* target)
{
	if (m_isSmarter)
		m_evade->setTargetActor(target);
	else
		m_flee->setTargetActor(target);
}

void Alien::onCollision(Actor* collidedActor)
{
	if (collidedActor->getID() == 2)
	{
		heal(1, collidedActor);
	}
	else if (collidedActor->getID() == 3)
	{
		MathLibrary::Vector2 worldPosition = getTransform()->getWorldPosition();
		MathLibrary::Vector2 collidedActorPosition = collidedActor->getTransform()->getWorldPosition();

		float distance = (worldPosition - collidedActorPosition).getMagnitude();

		if (distance <= 30)
			takeDamage(1, collidedActor);


	}
}
