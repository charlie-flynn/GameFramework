#pragma once
#include "Agent.h"
#include "Arrival.h"

class CursorChaser : public Agent
{
private:
	Arrival* m_arrival;
public:
	CursorChaser();
	CursorChaser(float x, float y);
	~CursorChaser();

	void start() override;
	void update(float deltaTime) override;
	void draw() override;
};