#pragma once
#include "Scene.h"
#include "Pathfinding/NodeMap.h"

class SampleScene :
    public Scene
{
private:
    Pathfinding::NodeMap m_nodeMap;

public:
    SampleScene();

    void start() override;
    void update(float deltaTime) override;
};

