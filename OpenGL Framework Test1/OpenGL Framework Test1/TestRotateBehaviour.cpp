#include "TestRotateBehaviour.h"
#include "GameObject.h"
#include "Utils.h"

TestRotateBehaviour::TestRotateBehaviour()
{
	m_active = true;
}

TestRotateBehaviour::~TestRotateBehaviour()
{
}

void TestRotateBehaviour::start()
{
}

void TestRotateBehaviour::update()
{
	m_parentObject->localTransform.getRot().y += Time::deltaTime * 1.f;
}

void TestRotateBehaviour::render()
{

}

void TestRotateBehaviour::renderTransparent()
{
}

void TestRotateBehaviour::renderGUI()
{
}
