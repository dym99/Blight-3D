#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include <string>

//Cannot include file "GameObject.exe" (recursive file include)
//	so tell the behaviour that GameObject exists so we can use its typename.
class GameObject;
//
//


class Behaviour abstract
{
public:
	//Called on events
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void renderTransparent() = 0;
	virtual void renderGUI() = 0;

	void setParentObject(GameObject* _parent);

	//Helpers
	void setActive(bool _active);
	bool isActive() const;
protected:
	std::string m_name;
	bool m_active;

	GameObject *m_parentObject;
};

#endif