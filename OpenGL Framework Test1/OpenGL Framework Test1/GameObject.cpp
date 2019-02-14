#include "GameObject.h"



GameObject::GameObject(const std::string& _name)
{
	localTransform = Transform();
	worldTransform = {	{1,0,0,0},
						{0,1,0,0},
						{0,0,1,0},
						{0,0,0,1} };

	m_behaviours = std::vector<Behaviour*>();
	m_children   = std::vector<GameObject*>();

	m_name = _name;

	m_parent = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::addChild(GameObject *_child)
{
	//Return if child is already
	for (unsigned int i = 0; i < m_children.size(); ++i) {
		if (m_children[i] == _child) {
			return;
		}
	}
	//Add the child
	_child->m_parent = this;
	m_children.push_back(_child);
}

void GameObject::removeChildren()
{
	m_children.clear();
}

void GameObject::removeChild(GameObject * _child)
{
	for (int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i] == _child)
			m_children.erase(m_children.begin() + i);
	}
}

void GameObject::addBehaviour(Behaviour *_behaviour)
{
	//Give the behaviour a handle to the object and add it to the list.
	_behaviour->setParentObject(this);
	m_behaviours.push_back(_behaviour);
}

void GameObject::update()
{
	if (m_parent) {
		worldTransform = m_parent->worldTransform * localTransform.getModel();
	}

	//Update all active behaviours
	for (unsigned int i = 0; i < m_behaviours.size(); ++i) {
		if (m_behaviours[i]->isActive())
			m_behaviours[i]->update();
	}

	//Update all children
	for (unsigned int i = 0; i < m_children.size(); ++i) {
		m_children[i]->update();
	}
}

void GameObject::onRender()
{
	//Call behaviour render function
	for (unsigned int i = 0; i < m_behaviours.size(); ++i) {
		if (m_behaviours[i]->isActive())
			m_behaviours[i]->render();
	}
	//Call render function for all children.
	for (unsigned int i = 0; i < m_children.size(); ++i) {
		m_children[i]->onRender();
	}
}

void GameObject::onRenderTransparent()
{
	//TODO: Transparency
}

void GameObject::onRenderGUI()
{
	//Call behaviour render function
	for (unsigned int i = 0; i < m_behaviours.size(); ++i) {
		m_behaviours[i]->renderGUI();
	}
}

std::vector<GameObject*> *GameObject::getChildren()
{
	return &m_children;
}
std::vector<Behaviour*> *GameObject::getBehaviours()
{
	return &m_behaviours;
}

GameObject * GameObject::getParent()
{
	return m_parent;
}

std::string GameObject::getName()
{
	return m_name;
}
