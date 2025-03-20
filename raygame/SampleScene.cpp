#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"

#include "CursorChaser.h"
#include "SampleAgent.h"
#include "Hunter.h"

#include <raylib.h>
#include <string>

#include "Pathfinding/Pathfinding.h"
#include "Pathfinding/NodeMap.h"

#include "Alien.h"

SampleScene::SampleScene() : Scene(), m_nodeMap(Pathfinding::NodeMap())
{

}

void SampleScene::start()
{
	std::vector<std::string> asciimap;
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0111111111111000111111111110");
	asciimap.push_back("0111111111111000111111111110");
	asciimap.push_back("0111111111111000111111111110");
	asciimap.push_back("0111111111111111111111111110");
	asciimap.push_back("0111000000111000111111111110");
	asciimap.push_back("0111000000111000111111111110");
	asciimap.push_back("0111000000111000000100010000");
	asciimap.push_back("0111000000111000000100010000");
	asciimap.push_back("0111000000111000000100010000");
	asciimap.push_back("0111111111111111111111111110");
	asciimap.push_back("0111111111111111111111111110");
	asciimap.push_back("0111111111111111111111111110");
	asciimap.push_back("0111111111111111111111111110");
	asciimap.push_back("0010000000000000000000000100");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110111111111111110");
	asciimap.push_back("0111111111110000000000010000");
	asciimap.push_back("0111111111110000000000010000");
	asciimap.push_back("0111111111110000000000010000");
	asciimap.push_back("0111111111111111111111110000");
	asciimap.push_back("0111111111110000000000000000");
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0000000000000000000000000000");
	asciimap.push_back("0000000000000000000000000000");

	m_nodeMap.cellSize = 25;
	m_nodeMap.Initialise(asciimap);

	Alien* alien = new Alien(&m_nodeMap, 200, 200);
	addActor(alien);

	Alien* alienB = new Alien(&m_nodeMap, 280, 200);
	addActor(alienB);

	Alien* alienC = new Alien(&m_nodeMap, 360, 200);
	addActor(alienC);

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
	m_nodeMap.Draw(true);

	//m_nodeMap.Draw(true);
	/*
	DrawText(std::to_string(deltaTime).c_str(), 20, 20, 20, WHITE);
	DrawFPS(20, 50);

	Pathfinding::Node a(100, 100);
	Pathfinding::Node b(200, 100);
	Pathfinding::Node c(100, 300);

	a.ConnectTo(&b, 1.0f);
	a.ConnectTo(&c, 4.0f);
	b.ConnectTo(&c, 1.0f);

	std::vector<Pathfinding::Node*> path = Pathfinding::DijkstrasSearch(&a, &c);
	*/

	//Pathfinding::DrawGraph(&a, &list);

	/*
	List<Pathfinding::Node*> path = { &a, &b, &c };
	Pathfinding::DrawPath(path, RED);

	Pathfinding::DrawNode(&a, false);
	Pathfinding::DrawNode(&b, true);
	Pathfinding::DrawNode(&c, false);
	*/
}
