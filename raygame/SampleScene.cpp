#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "SampleAgent.h"
#include "CursorChaser.h"
#include "Pursue.h"
#include "Evade.h"

void SampleScene::start()
{
	//This is a better comment

	SampleAgent* test = new SampleAgent(250, 250);
	addActor(test);

	CursorChaser* cursorGuy = new CursorChaser(200, 200);
	addActor(cursorGuy);

	test->addBehavior(new Pursue(test, 1.0f, cursorGuy));



	/*
	Actor* test = new Actor(50, 50, "Test");
	SpriteComponent* sprite = new SpriteComponent(test, "Images/player.png");
	test->addComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });

	addActor(test);
	*/
}
