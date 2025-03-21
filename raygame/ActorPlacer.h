#pragma once
#include "Actor.h"
#include "Pathfinding/NodeMap.h"

class SpriteComponent;

enum EPlaceableActors
{
	WALTERBERRY = 0,
	EMU_DOG,
	ALIEN
};

class ActorPlacer : public Actor
{
private:
	SpriteComponent* m_spriteOne;
	SpriteComponent* m_spriteTwo;
	SpriteComponent* m_spriteThree;

	EPlaceableActors m_selected;

	Pathfinding::NodeMap* m_nodeMap;
public:
	ActorPlacer(Pathfinding::NodeMap* nodeMap);

	void start() override;
	void update(float deltaTime) override;

	void draw() override;

};