#include "PathScene.h"

void PathScene::start()
{
	Scene::start();

	m_nodeMap.cellSize = 32;
	std::vector<std::string> asciiMap;
	asciiMap.push_back("000000000000000000");
	asciiMap.push_back("011111111111111110");
	asciiMap.push_back("011111110101111110");
	asciiMap.push_back("011111110101111110");
	asciiMap.push_back("011111110101111110");
	asciiMap.push_back("011111111111111110");
	asciiMap.push_back("000000000000000000");

	m_nodeMap.Initialise(asciiMap);

	m_pathAgent = new Pathfinding::PathAgent();
	m_pathAgent->SetNode(m_nodeMap.GetNode(1, 1));
	m_pathAgent->speed = 255;
}

void PathScene::update(float deltaTime)
{
	Color lineColor = { 255, 255, 255, 255 };

	bool drawNodeMap = true;

	m_nodeMap.Draw(true);
	Pathfinding::DrawPath(m_pathAgent->path, lineColor);

	// read mouseclicks, left for start node, end for right node
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		Pathfinding::Node* end = m_nodeMap.GetClosestNode(mousePos);
		m_pathAgent->GoToNode(end);
	}

	Scene::update(deltaTime);

	m_pathAgent->Update(deltaTime);
	m_pathAgent->Draw();
}

void PathScene::end()
{
	Scene::end();
	delete m_pathAgent;

}
