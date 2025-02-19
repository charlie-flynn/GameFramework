#pragma once
#include "Agent.h"
#include "Seek.h"

class SampleAgent : public Agent
{
private:
	Seek* behavior;
public:
	void start() override;
	void update(float deltaTime) override;
	void draw() override;
};