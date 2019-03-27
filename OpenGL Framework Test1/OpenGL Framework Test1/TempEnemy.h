#pragma once
#include "Behaviour.h"
#include "Graph.h"

class Enemy;
class P_PhysicsBody;
class GameObject;
class Game;

class TempEnemy : public Behaviour
{
public:
	TempEnemy(P_PhysicsBody* _body, Enemy* _theEnemy, GameObject* _thePlayer, Graph* _theGraph, Node& _closest, Game* _game);
	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

	void die();
	void respawn();

	void setTargetNode(Node* _target);
	void setTargetNode(int _id);

	void setStartNode(Node* _start);
	void setStartNode(int _id);

	void calculatePath();

	void leap(glm::vec3 _at, float _speed, float _height = 1.f);

	Node* findClosestNode();
private:
	//How many times in a row has the player attacked?
	float health = 2.f;
	P_PhysicsBody *m_bodyObject;
	Enemy* m_theEnemy;
	GameObject* m_thePlayer;
	Graph* m_theGraph;
	float pathfindingTolerence = 0.1f;
	std::queue<Node*> m_path;

	Game* theGame;

	Node* m_targetNode;
	Node* m_startNode;
	Node* m_recentNode;
	Node* closestToLogun;
	Node* closestToL;
	int prevClosestID = -1;
};
