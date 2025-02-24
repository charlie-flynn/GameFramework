#pragma once
#include "Agent.h"

class Wander;
class Pursue;
class Seek;

enum State
{
	STATE_FIND = 0,
	STATE_STALK,
	STATE_PURSUE
};

class Hunter : public Agent
{
private:
	int m_state;
	Actor* m_target;

	Wander* m_wander;
	Pursue* m_pursue;
	Seek* m_seek;
public:
	Hunter();
	Hunter(float x, float y, Actor* target);
	~Hunter();

	void start() override;
	void update(float deltaTime) override;
	void draw() override;

private:
	void setState(int state);
};