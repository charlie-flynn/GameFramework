#pragma once
#include "Scene.h"
#include "BlackboardQuestion.h"
class SampleScene :
    public Scene
{
private:
    BlackboardQuestion* m_test;

public:
    SampleScene();

    void start() override;
    void update(float deltaTime) override;
};

