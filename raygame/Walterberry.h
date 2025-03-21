#pragma once
#include "Actor.h"
#include "SpriteComponent.h"

class Walterberry : public Actor
{
private:
	SpriteComponent* m_sprite;
	bool m_blackboardNoticePosted;
public:
	Walterberry(float x = 0, float y = 0);
	~Walterberry();

	void update(float deltaTime) override;
	void draw() override;
	void onCollision(Actor* collidedActor) override;
};