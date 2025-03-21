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
#include "Walterberry.h"
#include "EMUDog.h"

#include "ActorPlacer.h"

SampleScene::SampleScene() : Scene(), m_nodeMap(Pathfinding::NodeMap()), m_mapTexture(Texture2D())
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

	Alien* alienB = new Alien(&m_nodeMap, 200, 250);
	addActor(alienB);

	Alien* alienC = new Alien(&m_nodeMap, 200, 280);
	addActor(alienC);

	m_mapTexture = LoadTexture("Images/game map.png");

	ActorPlacer* placer = new ActorPlacer(&m_nodeMap);
	addUIElement(placer);

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
	BlackboardData* deletedActorData = getBlackboard()->getData((char*)"ActorDeleted!");
	BlackboardData* alienInvestigateData = getBlackboard()->getData((char*)"AlienCanInvestigate");

	if (deletedActorData && alienInvestigateData && deletedActorData->actorData == alienInvestigateData->actorData)
	{
		getBlackboard()->removeData((char*)"AlienCanInvestigate");
		m_investigateableActors.Remove(deletedActorData->actorData);
	}


	DrawTexture(m_mapTexture, 0, 0, { 255, 255, 255, 255 });
	Scene::update(deltaTime);
	
	BlackboardData* investigateableData = getBlackboard()->getData((char*)"AddToInvestigateQueue");
	if (investigateableData && investigateableData->dataType == DATA_ACTORPOINTER)
	{
		m_investigateableActors.Add(investigateableData->actorData);
		getBlackboard()->removeData((char*)"AddToInvestigateQueue");
	}

	if (m_investigateableActors.Length())
	{
		m_index++;
		if (m_index >= m_investigateableActors.Length())
			m_index = 0;

		getBlackboard()->replaceOrAddData((char*)"AlienCanInvestigate", new BlackboardData(m_investigateableActors[m_index]));
	}

	if (IsKeyPressed(KEY_F1))
	{
		m_debugDraw = m_debugDraw ? false : true;
	}

	if (m_debugDraw)
	{
		m_nodeMap.Draw(true);
	}




	//m_nodeMap.Draw(true);

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
