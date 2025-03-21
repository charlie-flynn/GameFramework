#pragma once
#include "Agent.h"
#include "Blackboard.h"

#include "Pathfinding/NodeMap.h"
#include "Arrival.h"
#include "Flee.h"
#include "Evade.h"
#include "Seek.h"
#include "Pursue.h"

#include "SpriteComponent.h"
#include "Pathfinding/PathComponent.h"



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
	PathComponent* m_pathComponent;
	Arrival* m_arrival;
	Flee* m_flee;
	Evade* m_evade;
	Seek* m_seek;
	Pursue* m_pursue;


	Pathfinding::NodeMap* m_nodeMap;
	SpriteComponent* m_sprite;

	bool m_isSmarter;
	bool m_isDead;
	int m_health;
	int m_maxHealth;

	float m_investigateTimer;
	float m_blastTimer;

public:
	Alien();
	Alien(float x, float y);
	Alien(Pathfinding::NodeMap* nodeMap, float x, float y);
	~Alien();

	void start() override;
	void update(float deltaTime) override;

	void draw() override;

	void setTarget(Actor* target) { m_target = target; }
	void setNodeMap(Pathfinding::NodeMap* nodemap) { m_nodeMap = nodemap; }

	void takeDamage(int damage = 1);
	void heal(int healing = 1);

	EAlienStateMachine getState() { return m_state; }

private:

	void wanderUpdate();
	void investigateUpdate(float deltaTime);
	void eatTargetUpdate();
	void blastTargetUpdate(float deltaTime);
	void fleeTargetUpdate();

	void setState(EAlienStateMachine state);
	void setBehaviorWeights(bool pathEnabled, float arrivalWeight, float fleeWeight, float seekWeight);

	void setSeekTarget(Actor* target);

	void setFleeTarget(Actor* target);

	void onCollision(Actor* collidedActor) override;
};
