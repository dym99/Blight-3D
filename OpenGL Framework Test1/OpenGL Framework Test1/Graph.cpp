#include "Graph.h"

Edge::Edge(Node* _n1, Node* _n2, float _weight)
{
	n1 = _n1;
	n2 = _n2;
	weight = _weight;
}

Edge::Edge(Node* _n1, Node* _n2)
{
	n1 = _n1;
	n2 = _n2;
	calculateWeight();
}

void Edge::calculateWeight()
{
	glm::vec3 dif = n1->pos - n2->pos;
	weight = sqrt(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z);
}

int Node::numNodes = 0;

Node::Node()
{
	pos = glm::vec3(0, 0, 0);
	id = numNodes;
	numNodes++;
}

Node::Node(glm::vec3 _pos)
{
	pos = _pos;
	id = numNodes;
	numNodes++;
}

Graph::Graph()
{
}

Graph::~Graph()
{
	for (Node* n : nodes)
	{
		if (n != nullptr)
			delete n;
		n = nullptr;
	}
	for (Edge* e : edges)
	{
		if (e != nullptr)
			delete e;
		e = nullptr;
	}
}

void Graph::addNode(Node * _node)
{
	nodes.push_back(_node);
}

void Graph::createNode(glm::vec3 _pos, std::vector<Node*> _conNodes)
{
	Node* theNode = new Node(_pos);
	nodes.push_back(theNode);

	for (Node* n2 : _conNodes)
	{
		createEdge(theNode, n2);
	}
}

void Graph::createNode(glm::vec3 _pos, std::vector<int> _conNodes)
{
	Node* theNode = new Node(_pos);
	nodes.push_back(theNode);

	for (int id : _conNodes)
	{
		Node* otherNode = getNodeById(id);
		if (otherNode != nullptr)
		{
			createEdge(theNode, otherNode);
		}
	}
}

void Graph::createNode(glm::vec3 _pos)
{
	Node* theNode = new Node(_pos);
	nodes.push_back(theNode);
}

void Graph::createNode()
{
	Node* theNode = new Node(glm::vec3());
	nodes.push_back(theNode);
}

Node * Graph::getNodeById(int _id)
{
	for (Node* n : nodes)
		if (n->id == _id)
			return n;
	return nullptr;
}

void Graph::addEdge(Edge * _edge)
{
	if (getNodeById(_edge->n1->id) != nullptr && getNodeById(_edge->n2->id) != nullptr)
		edges.push_back(_edge);
}

void Graph::createEdge(Node * _n1, Node * _n2)
{
	Edge* theEdge = new Edge(_n1, _n2);
	edges.push_back(theEdge);
	_n1->edges.push_back(theEdge);
	_n2->edges.push_back(theEdge);
	theEdge->calculateWeight();
}

float Graph::aStarTolerence = 0.001f;

std::queue<Node*> Graph::aStar(Node * _start, Node * _target, bool _recalculate)
{
	//This assumes all the nodes have had their weights calculated.
	//DONE: Changes to the algorithm must be made if the AI is required to move through a dynamic (moving or changing) graph.

	//When told, recalculate the edges for the entire graph. If only individual edges are to be changed
	//Call the calculateWeight function on the edges desired before calling aStar.
	if (_recalculate)
		for (Edge* e : edges)
			e->calculateWeight();

	//Intialize the nodes for searching, and ensure that both 
	//the start and target nodes are in the graph.
	bool startInGraph = false;
	bool targetInGraph = false;
	for (Node* n : nodes)
	{
		if (n == _start)
		{
			startInGraph = true;
			n->distFromStart = 0.f;
		}
		else if (n == _target)
		{
			targetInGraph = true;
			n->distFromStart = -1.f;
		}
		else
			n->distFromStart = -1.f;
		n->closed = false;
		n->distToEnd = -1.f;
	}

	//If the end is the start, return the start node.
	std::queue<Node*> path;
	path.push(_start);
	if (_start == _target)
	{
		return path;
	}

	//Delete the open list, so that
	//all nodes are currently neither open nor closed.
	openNodes.clear();

	Node* currentNode = _start;
	while (currentNode != _target)
	{
		currentNode->closed = true;
		//Remove from open nodes
		for (int i = 0; i < openNodes.size(); ++i)
		{
			if (openNodes[i] == currentNode)
				openNodes.erase(openNodes.begin() + i);
		}

		//For all the edges adjacent to the current node
		for (Edge* n : currentNode->edges)
		{
			//Point to the node at the other end of the edge
			Node* checkNode;
			if (n->n1 == currentNode)
				checkNode = n->n2;
			else
				checkNode = n->n1;

			//Do not visit a node that is closed. It has already been checked. We should check open nodes
			//They may be closer to the start then we first thought.
			if (checkNode->closed)
				continue;

			//Calculate the distance travelled from the start
			float possibleDist = currentNode->distFromStart + n->weight;
			if (possibleDist < checkNode->distFromStart || checkNode->distFromStart < 0)
				checkNode->distFromStart = possibleDist;

			//Calculate the heuristic value to the target. In this case, we use square magnitude of the physical distance between them.
			if (checkNode->distToEnd < 0)
			{
				glm::vec3 endVec = (checkNode->pos - _target->pos);
				checkNode->distToEnd = endVec.x * endVec.x + endVec.y * endVec.y + endVec.z + endVec.z;
			}

			//Add the node to the open list
			openNodes.push_back(checkNode);

			//Now all the adjacent nodes have been calculated for.
			//Pick the next node
		}

		if (openNodes.size() > 0)
		{
			currentNode = openNodes[0];
			for (Node* n : openNodes)
			{
				//Look at all the nodes in the open list
				//Check their calculated values, and pick the lowest one as the current node
				if (n->distFromStart + n->distToEnd < currentNode->distFromStart + n->distToEnd)
				{
					currentNode = n;
				}
			}
		}
		else
		{
			//No path was able to be found!
			//Return an empty queue
			std::queue<Node*> nullQueue;
			return nullQueue;
		}

		//The new node has been chosen. If it's not the target, repeat
	}
	//Target has been found!
	//The algorithm has found the target! Now, finally, assemble the path
	std::vector<Node*> reversePath;
	currentNode = _target;

	while (currentNode != _start)
	{
		for (Edge* e : currentNode->edges)
		{
			//For each node adjacent to the current node
			//Check if the current 
			Node* checkNode;
			if (e->n1 == currentNode)
				checkNode = e->n2;
			else
				checkNode = e->n1;
			if (abs(currentNode->distFromStart - e->weight - checkNode->distFromStart) <= aStarTolerence)
			{
				reversePath.push_back(currentNode);
				currentNode = checkNode;
				break;
			}

		}
	}

	//And as a last *last* step, compile the path into a queue.
	for (int i = reversePath.size() - 1; i >= 0; --i)
	{
		path.push(reversePath[i]);
	}

	return path;
}
