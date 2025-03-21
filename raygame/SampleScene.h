#pragma once
#include "Scene.h"
#include "Pathfinding/NodeMap.h"

class SampleScene :
    public Scene
{
private:
    Pathfinding::NodeMap m_nodeMap;
    Texture2D m_mapTexture;

    DynamicArray<Actor*> m_investigateableActors;
    int m_index;
    bool m_debugDraw;

public:
    SampleScene();

    void start() override;
    void update(float deltaTime) override;
};

