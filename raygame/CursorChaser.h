#pragma once
#include "Agent.h"
#include "Seek.h"

class CursorChaser : public Agent
{
private:
	Seek* m_seek;
public:
	CursorChaser();
	CursorChaser(float x, float y);

	void start() override;
	void update(float deltaTime) override;
	void draw() override;
};