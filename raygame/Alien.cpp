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

	setCollider(new CircleCollider(40, this));
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

	setCollider(new CircleCollider(40, this));
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
		// has a blaster, switches to any of the other four states
		// can also access memory to switch faster
		investigateUpdate();
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
		blastTargetUpdate();
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
				// get a random value between -1 and 1 for both the X and Y coordinates
				int randomIntX = (rand() % 2001) - 1000;
				int randomIntY = (rand() % 2001) - 1000;

				MathLibrary::Vector2 randomTarget = { (float)randomIntX / 1000, (float)randomIntY / 1000 };

				randomTarget.normalize();
				randomTarget = randomTarget * 15;

				randomTarget = randomTarget + actorPosition;

				m_arrival->setTargetPosition(randomTarget);

				setState(INVESTIGATE_STATE);
			}
		}
	}

	if (!m_nodeMap)
		return;

	// check if the current path is empty
	if (m_pathBehavior->isPathEmpty())
	{
		// if so, check if there is a node nearby, and if so, create a new path to another random node
		// otherwise, seek to the center of the window
		if (m_nodeMap->GetClosestNode(getTransform()->getWorldPosition().x, getTransform()->getWorldPosition().y) != nullptr)
		{
			m_seek->setWeight(0.0f);
			m_pathBehavior->setWeight(1.0f);

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
