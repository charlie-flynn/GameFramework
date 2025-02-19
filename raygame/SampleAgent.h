#pragma once
#include "Agent.h"
#include "Seek.h"

class SampleAgent : public Agent
{
private:
	Seek* m_behavior;
public:
	SampleAgent(float x, float y);
	void start() override;
	void update(float deltaTime) override;
	void draw() override;
};