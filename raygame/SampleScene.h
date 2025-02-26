#pragma once
#include "Scene.h"
class SampleScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
};

