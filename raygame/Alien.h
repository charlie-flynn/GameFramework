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

	bool m_isSmarter;

	Pathfinding::NodeMap* m_nodeMap;

	SpriteComponent* m_sprite;
public:
	Alien();
	Alien(float x, float y);
	Alien(Pathfinding::NodeMap nodeMap, float x, float y);

	void start() override;
	void update(float deltaTime) override;

	void setTarget(Actor* target) { m_target = target; }

private:

	void wanderUpdate();
	void investigateUpdate();
	void eatTargetUpdate();
	void blastTargetUpdate();
	void fleeTargetUpdate();

	void onEnterInvestigate();


};
