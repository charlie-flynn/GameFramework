#pragma once
#include "Component.h"
#include <vector>
#include "Pathfinding.h"

class PathComponent : public Component
{
private:
	std::vector<Pathfinding::Node*> m_path;
	float m_speed;

	int currentIndex;
	Pathfinding::Node* m_currentNode;
public:
	PathComponent(Actor* owner, float speed, std::vector<Pathfinding::Node*> path);

	void update(float deltaTime) override;

	void setSpeed(float speed) { m_speed = speed; }

	void setPath(std::vector<Pathfinding::Node*> path) { m_path = path; }
	bool isPathEmpty() { return m_path.empty(); }

};