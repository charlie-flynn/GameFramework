#pragma once
#include "Scene.h"
#include "BlackboardQuestion.h"
class SampleScene :
    public Scene
{
public:
    BlackboardQuestion test;

    void start() override;
    void update(float deltaTime) override;
};

