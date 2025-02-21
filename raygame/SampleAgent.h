#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"

class SampleAgent : public Agent
{
private:
	Seek* m_seek;
	Flee* m_flee;
public:
	SampleAgent(float x, float y);
	void start() override;
	void update(float deltaTime) override;
	void draw() override;
};