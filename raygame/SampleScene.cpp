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
	// big nodemap to give to the aliens
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
}

void SampleScene::update(float deltaTime)
{
	// check if the current data used to let aliens know an actor can be investigated isn't for a deleted actor
	BlackboardData* deletedActorData = getBlackboard()->getData((char*)"ActorDeleted!");
	BlackboardData* alienInvestigateData = getBlackboard()->getData((char*)"AlienCanInvestigate");

	if (deletedActorData && alienInvestigateData && deletedActorData->actorData == alienInvestigateData->actorData)
	{
		// if so, remove it from the blackboard and remove it from the investigateableActors list
		getBlackboard()->removeData((char*)"AlienCanInvestigate");
		m_investigateableActors.Remove(deletedActorData->actorData);
	}


	DrawTexture(m_mapTexture, 0, 0, { 255, 255, 255, 255 });
	Scene::update(deltaTime);
	
	// check if there is a call for something to be added to the list
	// if so, add it to the investigateableActors list
	BlackboardData* investigateableData = getBlackboard()->getData((char*)"AddToInvestigateQueue");
	if (investigateableData && investigateableData->dataType == DATA_ACTORPOINTER)
	{
		m_investigateableActors.Add(investigateableData->actorData);
		getBlackboard()->removeData((char*)"AddToInvestigateQueue");
	}

	// if there is anything in the list, swap out the current AlienCanInvestigate data for another
	// the effect this has is that every frame, one thing can be investigated by aliens
	// assuming there isnt a billion things this is good enough
	if (m_investigateableActors.Length())
	{
		m_index++;
		if (m_index >= m_investigateableActors.Length())
			m_index = 0;

		getBlackboard()->replaceOrAddData((char*)"AlienCanInvestigate", new BlackboardData(m_investigateableActors[m_index]));
	}

	// swaps the debug draw bool, which draws the nodemap if true
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
