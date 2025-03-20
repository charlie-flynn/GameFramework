#pragma once
#include "Agent.h"
#include "Blackboard.h"

#include "Pathfinding/NodeMap.h"
#include "Pathfinding/PathBehavior.h"
#include "Arrival.h"
#include "Flee.h"
#include "Evade.h"
#include "Seek.h"
#include "Pursue.h"

#include "SpriteComponent.h"

#include "CircleCollider.h"

enum EAlienStateMachine
{
	WANDER_STATE = 0,
	INVESTIGATE_STATE,
	EAT_TARGET_STATE,
	BLAST_TARGET_STATE,
	FLEE_TARGET_STATE
};

class Alien : public Agent
{
private:
	EAlienStateMachine m_state;
	Actor* m_target;

	// behaviors
	PathBehavior* m_pathBehavior;
	Arrival* m_arrival;
	Flee* m_flee;
	Evade* m_evade;
	Seek* m_seek;
	Pursue* m_pursue;


	Pathfinding::NodeMap* m_nodeMap;
	SpriteComponent* m_sprite;

	bool m_isSmarter;
	int m_health;

public:
	Alien();
	Alien(float x, float y);
	Alien(Pathfinding::NodeMap nodeMap, float x, float y);

	void start() override;
	void update(float deltaTime) override;

	void draw() override;

	void setTarget(Actor* target) { m_target = target; }
	void setNodeMap(Pathfinding::NodeMap* nodemap) { m_nodeMap = nodemap; }

private:

	void wanderUpdate();
	void investigateUpdate();
	void eatTargetUpdate();
	void blastTargetUpdate();
	void fleeTargetUpdate();

	void setState(EAlienStateMachine state);
	void setBehaviorWeights(float pathWeight, float arrivalWeight, float fleeWeight, float evadeWeight, float seekWeight, float pursueWeight);
};
