#pragma once
#include "Actor.h"
#include "Agent.h"

class Wander;
class Seek;
class Pursue;
class SpriteComponent;

class EMUDog : public Agent
{
private:
	Wander* m_wander;
	Seek* m_seek;
	Pursue* m_pursue;
	SpriteComponent* m_sprite;

	bool m_hasHat;
	bool m_blackboardNoticePosted;

	Actor* m_target;

	float m_lifeSpan;

public:
	EMUDog();
	EMUDog(float x, float y);

	void start() override;
	void update(float deltaTime) override;

	void draw() override;

	void onCollision(Actor* collidedActor) override;

private:
	void setSeekTarget(Actor* target);
	void setSeekWeight(float weight);
};