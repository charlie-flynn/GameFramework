#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "SampleAgent.h"
#include "CursorChaser.h"
#include "Pursue.h"
#include "Evade.h"

#include "Hunter.h"

void SampleScene::start()
{
	//This is a better comment

	CursorChaser* cursorGuy = new CursorChaser(200, 200);
	addActor(cursorGuy);

	Hunter* hunter = new Hunter(400, 400, cursorGuy);
	addActor(hunter);



	/*
	Actor* test = new Actor(50, 50, "Test");
	SpriteComponent* sprite = new SpriteComponent(test, "Images/player.png");
	test->addComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });

	addActor(test);
	*/
}
