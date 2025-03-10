#pragma once
#include "raylib.h"
#include "List.h"

namespace Pathfinding
{
	struct Node;

	struct Edge
	{
		Edge(Node* target = nullptr, float cost = 1.0f) : target(target), cost(cost) {}

		Node* target;
		float cost;
	};

	struct Node
	{
		Node(float x = 0, float y = 0) : 
			position(Vector2{x, y}), 
			gScore(0),  
			previous(nullptr),
			connections(List<Edge>()) {}

		Vector2 position;

		float gScore;
		Node* previous;

		List<Edge> connections;

		void ConnectTo(Node* other, float cost);
	};

	List<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	void DrawPath(List<Node*>& path, Color lineColor);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, List<Node*>* drawnList);
}