#include "TempEnemy.h"
#include "P_PhysicsBody.h"
#include "GameObject.h"
#include "Game.h"
#include "Enemy.h"
#include "Input.h"

#define CLOSEST_RAD 1.15f

TempEnemy::TempEnemy(P_PhysicsBody * _body, Enemy * _theEnemy, GameObject* _thePlayer, Graph* _theGraph, Node& _closest, Game* _game)
{
	m_thePlayer = _thePlayer;
	m_theEnemy = _theEnemy;
	m_bodyObject = _body;
	m_theGraph = _theGraph;
	m_active = true;
	closestToLogun = &_closest;
	theGame = _game;
}

void TempEnemy::start()
{
}

void TempEnemy::update()
{


	bool hitSword = false;
	for (std::string name : m_bodyObject->getTriggeredNames())
	{
		if (name == "Sword")
		{
			health -= 0.10f;
		}
	}

	//Chase the player

	//glm::vec3 vectorPT = (m_thePlayer->localTransform.getPos() - m_bodyObject->getPos());
	//float vectorL = sqrt((vectorPT.x * vectorPT.x) + (vectorPT.y * vectorPT.y) + (vectorPT.z * vectorPT.z));
	//if (vectorL > CLOSEST_RAD)
	//{
	//	glm::vec3 tingy = (glm::normalize(vectorPT)) * glm::vec3(50.f, 0.f, 50.f) - glm::vec3(0, 5, 0);
	//	m_bodyObject->P_addForce(tingy);
	//	std::cout << tingy.x << ", " << tingy.y << ", " << tingy.z << std::endl;
	//}

	//m_bodyObject->getGameObject()->localTransform.setScale(glm::vec3(1.f, health / 2, 1.f));

	closestToL = theGame->getClosestToLogun();

	if (prevClosestID != closestToL->id)
	{
		//Logun has moved to a new node.
		m_targetNode = m_theGraph->getNodeById(closestToL->id);
		m_startNode = findClosestNode();
		if (m_startNode == m_recentNode)
			m_startNode = m_path.front();
		calculatePath();

		prevClosestID = closestToL->id;
	}

	std::cout << closestToL->id << " " << prevClosestID << std::endl;

	//if (m_startNode == NULL)
	//{
	//	setStartNode(0);
	//	setTargetNode(0);
	//	calculatePath();
	//}

	if (m_startNode == m_targetNode || m_path.size() == 0)
	{
		//Target Logun
		bool touchGround = false;
		for (std::string _name : m_bodyObject->getTriggeredNames())
			if (_name == "Floor")
				touchGround = true;

		if (Input::GetKeyDown(KeyCode::F) || rand() % 100 < 1 && touchGround)
		{
			leap(m_thePlayer->localTransform.getPos(), 250.f, 10.f);
		}
		else
		{
			glm::vec3 vectorPT = (m_thePlayer->localTransform.getPos() - m_bodyObject->getPos());
			float vectorL = sqrt((vectorPT.x * vectorPT.x) + (vectorPT.y * vectorPT.y) + (vectorPT.z * vectorPT.z));
			if (vectorL > CLOSEST_RAD)
			{
				glm::vec3 tingy = ((vectorPT) / vectorL) * glm::vec3(100.f, 0.f, 100.f) - glm::vec3(0, 100, 0);
				m_bodyObject->P_addForce(tingy);
				//std::cout << tingy.x << ", " << tingy.y << ", " << tingy.z << std::endl;
			}
		}
	}
	else
	{
		//Pathfinding
		if (m_path.size() > 0)
		{
			glm::vec3 point = m_path.front()->pos;
			glm::vec3 dif = point - m_bodyObject->getPos();
			float dist = dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;

			glm::vec3 vectorPT = (m_path.front()->pos - m_bodyObject->getPos());
			glm::vec3 tingy = (glm::normalize(vectorPT)) * glm::vec3(100.f, 0.f, 100.f) - glm::vec3(0, 5, 0);
			m_bodyObject->P_addForce(tingy);

			if (dist - m_bodyObject->getCollider()->getHeight() <= 0)
			{
				m_recentNode = m_path.front();
				m_path.pop();
			}
		}
	}
	if (health <= 0.0f)
		die();
}

void TempEnemy::render()
{
}

void TempEnemy::renderTransparent()
{
}

void TempEnemy::renderGUI()
{
}

void TempEnemy::die()
{
	Game::killEnemy(m_theEnemy);
}

void TempEnemy::setTargetNode(Node * _target)
{
	m_targetNode = _target;
}

void TempEnemy::setTargetNode(int _id)
{
	setTargetNode(m_theGraph->getNodeById(_id));
}

void TempEnemy::setStartNode(Node * _start)
{
	m_startNode = _start;
}

void TempEnemy::setStartNode(int _id)
{
	setStartNode(m_theGraph->getNodeById(_id));
}

void TempEnemy::calculatePath()
{
	m_path = m_theGraph->aStar(m_startNode, m_targetNode);
}

void TempEnemy::leap(glm::vec3 _at, float _speed, float _height)
{
	glm::vec3 leapDir = glm::normalize(_at - m_bodyObject->getPos()) + glm::vec3(0, _height, 0);
	m_bodyObject->P_addForce(leapDir * _speed);
}

Node * TempEnemy::findClosestNode()
{
	if (m_theGraph->nodes.size() > 0)
	{
		Node* closest = m_theGraph->nodes[0];
		for (Node* n : m_theGraph->nodes)
		{
			glm::vec3 distPos = n->pos - m_bodyObject->getGameObject()->localTransform.getPos();
			glm::vec3 distPos2 = closest->pos - m_bodyObject->getGameObject()->localTransform.getPos();
			float _dist = glm::dot(distPos, distPos);
			float _dist2 = glm::dot(distPos2, distPos2);
			if (_dist < _dist2)
				closest = n;
		}
		return closest;
	}
	else
		return nullptr;
}
