#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include "Transform.h"
#include "Behaviour.h"

class GameObject
{
public:
	GameObject(const std::string& _name);
	virtual ~GameObject();

	//Add a child.
	void addChild(GameObject *_child);

	//Call the CPS on this object.
	void removeChildren();

	//Add a behaviour to this object.
	void addBehaviour(Behaviour *behaviour);

	//Update this and all child objects.
	void update();

	//Functions called on render.
	void onRender();
	void onRenderTransparent();
	void onRenderGUI();

	std::vector<GameObject*> *getChildren();
	std::vector<Behaviour*> *getBehaviours();

	GameObject* getParent();

	Transform localTransform;
	glm::mat4 worldTransform;
protected:
	std::string m_name;
	std::vector<GameObject*> m_children;
	std::vector<Behaviour*> m_behaviours;
	GameObject* m_parent;
};

#endif