#pragma once
#include "Scene.h"
#include "NodeMap.h"
#include "PathAgent.h"

class PathScene : public Scene
{
public:
	PathScene() = default;

	void start() override;
	void update(float deltaTime) override;
	void end() override;

private:
	Pathfinding::NodeMap m_nodeMap;
	Pathfinding::PathAgent* m_pathAgent;
};
