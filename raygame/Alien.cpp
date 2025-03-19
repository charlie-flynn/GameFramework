#include "Alien.h"
#include "Transform2D.h"
#include <random>

#include "Engine.h"
#include "Scene.h"

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

	m_sprite->setTextureRotating(false);
	addComponent(m_sprite);

	setState(WANDER_STATE);
}

void Alien::update(float deltaTime)
{
	Agent::update(deltaTime);
	m_sprite->draw();

	switch (m_state)
	{
	case WANDER_STATE:
		wanderUpdate();
		break;
	case INVESTIGATE_STATE:
		investigateUpdate();
		break;
	case EAT_TARGET_STATE:
		eatTargetUpdate();
		break;
	case BLAST_TARGET_STATE:
		blastTargetUpdate();
		break;
	case FLEE_TARGET_STATE:
		fleeTargetUpdate();
		break;
	default:
		m_state = WANDER_STATE;
		wanderUpdate();
		break;
	}


}

void Alien::wanderUpdate()
{
	BlackboardData* data = Engine::getCurrentScene()->getBlackboard()->getData((char*)"AlienCanInvestigate");

	if (data)
	{
		if (data->dataType == DATA_VECTOR2 /*&& distance check*/)
		{
			// get a random value between -1 and 1 for both the X and Y coordinates
			int randomIntX = (rand() % 2001) - 1000;
			int randomIntY = (rand() % 2001) - 1000;

			MathLibrary::Vector2 randomTarget = { (float)randomIntX / 1000, (float)randomIntY / 1000 };

			randomTarget.normalize();
			randomTarget = randomTarget * 15;

			randomTarget = randomTarget + data->vector2Data;

			m_arrival->setTargetPosition(randomTarget);

			setState(INVESTIGATE_STATE);
		}
	}

	if (!m_nodeMap)
		return;

	if (m_pathBehavior->isPathEmpty())
	{
		if (m_nodeMap->GetClosestNode(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y) != nullptr)
		{
			m_seek->setWeight(0.0f);

			Pathfinding::Node* randomNode;

			do
			{
				int randomX = std::rand() % m_nodeMap->width;
				int randomY = std::rand() % m_nodeMap->height;
				randomNode = m_nodeMap->GetNode(randomX, randomY);
			} while (!randomNode);

			std::vector<Pathfinding::Node*> path = Pathfinding::AStarSearch(m_nodeMap->GetClosestNode(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y), randomNode);

			path = Pathfinding::GetSmoothedPath(path);

			m_pathBehavior->setPath(&path);

		}
		else
		{
			m_seek->setTargetPosition(MathLibrary::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2));

			m_pathBehavior->setWeight(0.0f);
			m_seek->setWeight(1.0f);
		}
	}
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

void Alien::setState(EAlienStateMachine state)
{
	m_state = state;

	switch (m_state)
	{
	case WANDER_STATE:	
		setBehaviorWeights(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case INVESTIGATE_STATE:
		setBehaviorWeights(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case EAT_TARGET_STATE:
		if (m_isSmarter)
			setBehaviorWeights(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		else
			setBehaviorWeights(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		break;
	case BLAST_TARGET_STATE:
		if (m_isSmarter)
			setBehaviorWeights(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		else
			setBehaviorWeights(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		break;
	case FLEE_TARGET_STATE:
		if (m_isSmarter)
			setBehaviorWeights(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		else
			setBehaviorWeights(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		break;
	default:
		break;
	}
}

void Alien::setBehaviorWeights(float pathWeight, float arrivalWeight, float fleeWeight, float evadeWeight, float seekWeight, float pursueWeight)
{
	m_pathBehavior->setWeight(pathWeight);
	m_arrival->setWeight(arrivalWeight);
	m_flee->setWeight(fleeWeight);
	m_evade->setWeight(evadeWeight);
	m_seek->setWeight(seekWeight);
	m_pursue->setWeight(pursueWeight);
}
