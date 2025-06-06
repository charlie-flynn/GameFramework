#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

namespace Pathfinding {
	struct Node;

	struct Edge {
		Edge() { target = nullptr; cost = 0; }
		Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

		Node* target;
		float cost;
	};

	struct Node {

		Node() {}
		Node(float x, float y) { position.x = x; position.y = y; gScore = 0; hScore = 0; previous = nullptr; }

		Vector2 position;

		float gScore;
		float hScore;
		Node* previous;

		std::vector<Edge> connections;

		void ConnectTo(Node* other, float cost);
	};

	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);
	std::vector<Node*> GetSmoothedPath(std::vector<Node*> path);
	void DrawPath(std::vector<Node*>& path, Color lineColor);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, std::vector<Node*>* drawnList);
}