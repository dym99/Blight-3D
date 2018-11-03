#include "Behaviour.h"

void Behaviour::setParentObject(GameObject * _parent)
{
	m_parentObject = _parent;
}

void Behaviour::setActive(bool _active)
{
	m_active = _active;
}

bool Behaviour::isActive() const
{
	return m_active;
}
