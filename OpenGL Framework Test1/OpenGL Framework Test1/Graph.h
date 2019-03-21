#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <queue>

struct Node;
struct Edge;

struct Graph
{
	// A graph is an abstract datatype.
	// Here, we use it for pathfinding.
	// It represents the desired paths for our
	// AI to follow.
	Graph();
	~Graph();
	// Add an existing node to the graph
	void addNode(Node* _node);
	// Add a new node to the graph
	void createNode(glm::vec3 _pos, std::vector<Node*> _conNodes);
	void createNode(glm::vec3 _pos, std::vector<int> _conNodes);
	void createNode(glm::vec3 _pos);
	void createNode();

	// Returns the node at the given id if it is part
	// of the graph. Returns nullptr otherwise
	Node* getNodeById(int _id);

	void addEdge(Edge* _edge);
	void createEdge(Node* _n1, Node* _n2);

	std::vector<Node*> nodes;
	std::vector<Edge*> edges;

	//All for use in A* algorithm
	std::queue<Node*> aStar(Node* _start, Node* _target, bool _recalculate = false);
	std::vector<Node*> openNodes;

	static float aStarTolerence;
};

struct Node
{
	Node();
	Node(glm::vec3 _pos);
	glm::vec3 pos;
	int id;

	std::vector<Edge*> edges;

	static int numNodes;

	//Used for A*
	float distFromStart;
	float distToEnd;
	bool closed;
};

struct Edge
{
	Edge(Node* _n1, Node* _n2, float _weight);
	Edge(Node* _n1, Node* _n2);

	void calculateWeight();

	Node* n1;
	Node* n2;
	float weight;
};