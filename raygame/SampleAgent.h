#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"
#include "Pathfinding/PathBehavior.h"

class SampleAgent : public Agent
{
private:
	Seek* m_seek;
	Flee* m_flee;
	Wander* m_wander;
	PathBehavior* m_pathBehavior;
public:
	SampleAgent(float x, float y);
	void start() override;
	void update(float deltaTime) override;
	void draw() override;

	void setPath(std::vector<Pathfinding::Node*>* path) { m_pathBehavior->setPath(path); }
};