#pragma once
#include "Behavior.h"
#include <vector>
#include "Pathfinding.h"

class PathBehavior : public Behavior
{
private:
	std::vector<Pathfinding::Node*>* m_path;
public:
	PathBehavior(Actor* owner, float weight, std::vector<Pathfinding::Node*>* path);

	void update(float deltaTime) override;

	void setPath(std::vector<Pathfinding::Node*>* path);
	bool isPathEmpty() { return m_path->empty(); }
};