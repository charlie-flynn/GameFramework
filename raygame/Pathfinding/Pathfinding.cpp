#include "Pathfinding.h"
#include <stdio.h>


namespace Pathfinding
{
	void Pathfinding::Node::ConnectTo(Node* other, float cost)
	{
		connections.PushBack(Edge(other, cost));
	}

	bool NodeSort(Node* left, Node* right)
	{
		return (left->gScore < right->gScore);
	}

	List<Node*> DijkstrasSearch(Node* startNode, Node* endNode)
	{
		{
			//Validate the input
			if (startNode == nullptr || endNode == nullptr)
			{
				return List<Node*>();
			}

			if (startNode == endNode)
			{
				List<Node*> singleNodePath;
				singleNodePath.PushBack(startNode);
				return singleNodePath;
			}

			//Initialize the starting node
			startNode->gScore = 0;
			startNode->previous = nullptr;

			//Create our temporary lists for storing nodes
			List<Node*> openList = List<Node*>();
			List<Node*> closedList = List<Node*>();

			//Add the starting node to openList
			openList.PushBack(startNode);


			while (openList.GetLength() > 0)
			{
				//Set the current node to the first node in the openList
				//and Remove currentNode from openList
				Node* currentNode = openList.PopFront();
				//Add currentNode to closedList
				closedList.PushBack(currentNode);

				//If the destination node was added to the closed list,
				//the shortest path has been found
				if (currentNode == endNode)
				{
					break;
				}

				//For each Edge e in currentNode's connections
				for (Edge e : currentNode->connections)
				{
					//If the target node is in the closedList, ignore it
					if (closedList.find(e.target) != closedList.end()) {
						continue;
					}
					//If the target node is not in the openList, update it
					if (openList.find(e.target) == closedList.end()) {
						//Calculate the target node's G Score
						e.target->gScore = currentNode->gScore + e.cost;
						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
						//Find the earliest point we should insert the node
						//to the list to keep it sorted
						int index = 0;
						for (auto i = openList.begin(); i != openList.end(); i++, index++) 
						{
							if (e.target->gScore < (*i)->gScore) 
							{
								break;
							}
						}
						openList.Insert(e.target, index);
					}
					//Otherwise the target node IS in the open list
					else {
						//Compare the new G Score to the old one before updating
						if (currentNode->gScore + e.cost < e.target->gScore) {
							//Calculate the target node's G Score
							e.target->gScore = currentNode->gScore + e.cost;
							//Set the target node's previous to currentNode
							e.target->previous = currentNode;
						}
					}
				}
			}

			//Create path in reverse from endNode to startNode
			List<Node*> path;
			Node* currentNode = endNode;

			while (currentNode != nullptr)
			{
				//Add the current node to the beginning of the path
				path.PushFront(currentNode);
				//Go to the previous node
				currentNode = currentNode->previous;
			}

			return path;
		}
	}

	void Pathfinding::DrawPath(List<Node*>& path, Color lineColor)
	{
		auto currentIter = path.begin();
		auto previousIter = currentIter;
		currentIter++;
		
		for (currentIter; currentIter != path.end(); currentIter++, previousIter++)
		{
			DrawLine((*previousIter)->position.x, (*previousIter)->position.y, (*currentIter)->position.x, (*currentIter)->position.y, lineColor);
		}
	}

	void Pathfinding::DrawNode(Node* node, bool selected)
	{
		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 25, YELLOW);
		//Draw the inner circle
		if (selected)
		{
			DrawCircle(node->position.x, node->position.y, 22, BROWN);
		}
		else
		{
			DrawCircle(node->position.x, node->position.y, 22, BLACK);
		}
		//Draw the text
		DrawText(buffer, node->position.x - 10, node->position.y - 10, 15, WHITE);
	}

	void Pathfinding::DrawGraph(Node* node, List<Node*>* drawnList)
	{
		DrawNode(node);
		drawnList->PushBack(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);
			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			DrawText(buffer, costPos.x, costPos.y, 15, WHITE);
			//Draw the target node
			//if (drawnList->find)
			//if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end())
			if (drawnList->find(e.target) == drawnList->end())
			{
				DrawGraph(e.target, drawnList);
			}
		}
	}
}
