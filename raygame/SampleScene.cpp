#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "CursorChaser.h"

#include "Hunter.h"

#include <raylib.h>
#include <string>

void SampleScene::start()
{
	//This is a better comment

	CursorChaser* cursorGuy = new CursorChaser(200, 200);
	addActor(cursorGuy);

	//Hunter* hunter = new Hunter(400, 400, nullptr);
	//addActor(hunter);



	/*
	Actor* test = new Actor(50, 50, "Test");
	SpriteComponent* sprite = new SpriteComponent(test, "Images/player.png");
	test->addComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });

	addActor(test);
	*/
}

void SampleScene::update(float deltaTime)
{
	Scene::update(deltaTime);
	DrawText(std::to_string(deltaTime).c_str(), 20, 20, 20, WHITE);
	DrawFPS(20, 50);
}
