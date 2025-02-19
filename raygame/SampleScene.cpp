#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "SampleAgent.h"

void SampleScene::start()
{
	//This is a better comment

	SampleAgent* test = new SampleAgent(500, 500);
	addActor(test);

	/*
	Actor* test = new Actor(50, 50, "Test");
	SpriteComponent* sprite = new SpriteComponent(test, "Images/player.png");
	test->addComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });

	addActor(test);
	*/
}
