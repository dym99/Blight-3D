#include "P_PhysicsBody.h"
#include "GL/glew.h"
#include "GameObject.h"
#define VEC3I glm::vec3(1, 0, 0)
#define VEC3J glm::vec3(0, 1, 0)
#define VEC3K glm::vec3(0, 0, 1)
#define frictionScalar 10.f


std::vector<P_PhysicsBody*> P_PhysicsBody::P_bodyCount{};

P_PhysicsBody::P_PhysicsBody()
{
	P_mass = 1.0f;
	P_bodyCount.push_back(this);
	P_netForce = VEC3ZERO;
	P_acceleration = VEC3ZERO;
	P_velocity = VEC3ZERO;
	P_name = "Default Body";
}

P_PhysicsBody::P_PhysicsBody(GameObject * _gameObject, float _mass, bool _gravity, P_Collider_Type _type, float _h, float _w, float _d, glm::vec3 _offset, float _bounciness, float _friction, bool _kinematic, bool _trigger, std::string _name, P_FlagType _flag)
{
	P_gameObject = _gameObject;
	if (!_gameObject->getParent())
		P_position = _gameObject->localTransform.getPos();
	else
		P_position = (glm::vec3)(_gameObject->getParent()->worldTransform * glm::vec4(_gameObject->localTransform.getPos(), 1.0f));
	P_bounciness = _bounciness;
	P_friction = _friction;
	P_mass = _mass;
	P_useGravity = _gravity;
	P_collider = new P_Collider(_type, _h, _w, _d);
	P_collider->setOffset(_offset);
	P_isKinematic = _kinematic;
	startPos = P_position;
	P_isTrigger = _trigger;
	P_name = _name;
	P_flags.push_back(_flag);

	P_bodyCount.push_back(this);
	P_netForce = VEC3ZERO;
	P_acceleration = VEC3ZERO;
	P_velocity = VEC3ZERO;
}

P_PhysicsBody::P_PhysicsBody(GameObject * _gameObject, float _mass, bool _gravity, bool _kinematic)
{
	P_gameObject = _gameObject;
	if (!_gameObject->getParent())
		P_position = _gameObject->localTransform.getPos();
	else
		P_position = (glm::vec3)(_gameObject->getParent()->worldTransform * glm::vec4(_gameObject->localTransform.getPos(), 1.0f));
	P_mass = _mass;
	P_useGravity = _gravity;
	P_isKinematic = _kinematic;
	startPos = P_position;
	P_flags.push_back(F_DEFAULT);
	P_name = "Default Name";

	P_bodyCount.push_back(this);
	P_netForce = VEC3ZERO;
	P_acceleration = VEC3ZERO;
	P_velocity = VEC3ZERO;
}

P_PhysicsBody::~P_PhysicsBody()
{
	for (int i = 0; i < P_bodyCount.size(); i++)
	{
		if (P_bodyCount[i] == this)
		{
			P_bodyCount.erase(P_bodyCount.begin() + i);
			break;
		}
	}
	
	if(P_collider != nullptr)
		delete P_collider;
}


P_CollisionData P_PhysicsBody::P_checkBounds(int i, int o)
{
	//Compare bounding sphere
	float radii = P_bodyCount[i]->P_collider->getMaxSize() + P_bodyCount[o]->P_collider->getMaxSize(); 

	glm::vec3 posi, poso;

	if (!P_bodyCount[i]->getGameObject()->getParent())
		posi = P_bodyCount[i]->getGameObject()->localTransform.getPos();
	else
		posi = (glm::vec3)(P_bodyCount[i]->P_gameObject->getParent()->worldTransform * glm::vec4(P_bodyCount[i]->P_gameObject->localTransform.getPos(), 1.0f));

	if (!P_bodyCount[o]->getGameObject()->getParent())
		poso = P_bodyCount[o]->getGameObject()->localTransform.getPos();
	else
		poso = (glm::vec3)(P_bodyCount[o]->P_gameObject->getParent()->worldTransform * glm::vec4(P_bodyCount[o]->P_gameObject->localTransform.getPos(), 1.0f));


	glm::vec3 vectorBetween(posi + P_bodyCount[i]->P_collider->getOffset() -
							poso + P_bodyCount[o]->P_collider->getOffset());

	float distanceSQ = (vectorBetween.x * vectorBetween.x + vectorBetween.y * vectorBetween.y + vectorBetween.z * vectorBetween.z);

	if (radii * radii < distanceSQ)
		return P_CollisionData();

	if (P_bodyCount[i]->P_collider->getType() == SPHERE && P_bodyCount[o]->P_collider->getType() == SPHERE)
		return P_CollisionData((radii - sqrt(distanceSQ)), vectorBetween, vectorBetween);
	return P_checkCollision(i, o);
}

P_CollisionData P_PhysicsBody::P_checkCollision(int i, int o)
{
	P_PhysicsBody* body1 = P_bodyCount[i];
	P_PhysicsBody* body2 = P_bodyCount[o];

	if (body1->P_collider == nullptr || body2->P_collider == nullptr)
	{
		//One or more collider doesn't exist
		return P_CollisionData();
	}

	//Shuffle order so only six calculations must be typed out
	if ((body1->P_collider->getType() == SPHERE
		&& body2->P_collider->getType() != SPHERE) ||
		(body1->P_collider->getType() == BOX
			&& body2->P_collider->getType() == CAPSULE))
	{
		return P_checkCollision(o, i);
	}


	std::vector<glm::vec3> pointsToTest{};
	//glm::mat3 totalRot = genRotMatrix(body1->P_gameObject->localTransform);
	glm::mat3 totalRot = body1->P_gameObject->worldTransform;

	if (body1->P_collider->getType() == CAPSULE)
	{
		if (body2->P_collider->getType() == CAPSULE)
		{

		}
		else if (body2->P_collider->getType() == BOX)
		{

		}
		else if (body2->P_collider->getType() == SPHERE)
		{

		}

		glm::vec3 direction = VEC3J * totalRot;
		glm::vec3 pointOnLine = body1->P_position + body1->P_collider->getOffset();

		for (int i = 0; i < pointsToTest.size(); i++)
		{
			//f = (dxpx + dypy + dzpz) / (dx^2 + dy^2 + dz^2) ~Where f is a scalar away from P (a point on the line) and D the direction, assume the point to find the closest point on the line to is at the origin.

		}
	}
	else if (body1->P_collider->getType() == BOX)
	{

		if (body2->P_collider->getType() == BOX)
		{
			
		}
		else
		{
			//SPHERE <-> BOX Collision!!!
			
			glm::vec3 Current = body2->P_position + body2->getCollider()->getOffset();
			glm::vec3 Target = body1->P_position + body1->getCollider()->getOffset();
			//Quaternion TargetRot = target.transform.rotation;
			//Quaternion rotInv = Quaternion.Inverse(TargetRot);
			
			Current = Current - Target;
			//Current = rotInv * Current;
			//Target = rotInv * Target;
			glm::vec3 size(body1->getCollider()->getWidth() * 0.5, body1->getCollider()->getHeight() * 0.5, body1->getCollider()->getDepth() * 0.5);
			
			float valX = findClosestOnCube(Current.x, size.x);
			float valY = findClosestOnCube(Current.y, size.y);
			float valZ = findClosestOnCube(Current.z, size.z);
			
			glm::vec3 closestPoint(valX, valY, valZ);
			closestPoint = closestPoint + Target;
			
			//closestPoint = TargetRot * closestPoint;
			//Target = TargetRot * Target;
			//Current = TargetRot * Current;
			Current = Current + Target;

			//Line between Current and Closest Point to be used as normal;
			float rad = body2->getCollider()->getHeight();
			
			//Return this value for the collision
			bool col = MagnitudeSquared(Current - closestPoint) < (rad * rad);
			if (col)
			{
				//Calculate depth from the closest point on the cube, the current point of the sphere, and the radius
				glm::vec3 normal = Current - closestPoint;
				float normalL = glm::length(normal);
				return P_CollisionData(rad - normalL, normal, normal);
			}
			else
				return P_CollisionData();
		}
	}
	//SPHERE <-> SPHERE calculations are handled above

	//Unkown collision shape(s). Return null
	return P_CollisionData();
}

void P_PhysicsBody::P_physicsUpdate(float dt)
{
	if (dt < 0.1f)
	{
		const int numBodies = P_bodyCount.size();
		for (int i = 0; i < numBodies; i++)
		{
			if (P_bodyCount[i] == nullptr)
			{
				P_bodyCount.erase(P_bodyCount.begin() + i);
				i--;
				continue;
			}

			P_bodyCount[i]->P_triggered = false;
			if (P_bodyCount[i]->P_trackNames)
			{
				P_bodyCount[i]->P_triggeredNames.clear();
			}
			P_PhysicsBody* body1 = P_bodyCount[i];

			//Update internal position to current position
			if (body1->getGameObject()->getParent())
				body1->P_position = body1->P_gameObject->getParent()->worldTransform * glm::vec4(body1->P_gameObject->localTransform.getPos(), 1.0f);
			else
				body1->P_position = body1->P_gameObject->localTransform.getPos();

			if (!body1->P_isKinematic)
			{
				//Apply forces
				if (body1->P_useGravity)
					body1->P_addForce(glm::vec3(0, P_GRAVITY, 0));

				body1->P_acceleration = body1->P_netForce / body1->P_mass;
				body1->P_velocity += body1->P_acceleration * dt;
				body1->P_position += body1->P_velocity * dt;

				//Update current position
				if (body1->getGameObject()->getParent())
					body1->P_gameObject->localTransform.setPos(body1->P_position - (glm::vec3)(body1->getGameObject()->getParent()->worldTransform * glm::vec4(VEC3ZERO, 1.0f)));
				else
					body1->P_gameObject->localTransform.setPos(body1->P_position);
			}

			// TODO: Add Tunneling check.

			//Check collisions
			if (numBodies > 1)
				for (int o = 0; o < numBodies; o++)
				{
					if (P_bodyCount[o] == nullptr)
					{
						P_bodyCount.erase(P_bodyCount.begin() + o);
						o--;
						continue;
					}

					P_PhysicsBody* body2 = P_bodyCount[o];
					//Two kinematic bodies would not react to one another, thus do not calculate for them.
					if ((body1->P_isKinematic && body2->P_isKinematic) || i == o || body1 == body2)
						continue;

					P_CollisionData colData = P_checkBounds(i, o);
					if (colData.didCollide)
					{
						body1->P_triggered = true;
						body2->P_triggered = true;

						if (body1->P_trackNames)
							body1->P_triggeredNames.push_back(body2->P_name);
						if (body2->P_trackNames)
							body2->P_triggeredNames.push_back(body2->P_name);

						/*COLLISION HAS BEEN DETECTED*/
						/*
							Here we reach a fork in the road
							If either of the involved objects are a trigger,
							or if one is flagged with a flag that the other ignores,
							then we entirely skip this step.
						*/

						if (!(body1->P_isTrigger == true || body2->P_isTrigger == true))
						{
							P_PhysicsBody* kinematicBody = nullptr;
							P_PhysicsBody* otherBody = nullptr;

							if (body1->P_isKinematic)
							{
								kinematicBody = body1;
								otherBody = body2;
							}
							else if (body2->P_isKinematic)
							{
								kinematicBody = body2;
								otherBody = body1;
							}

							if (body1->P_isKinematic || body2->P_isKinematic)
							{
								//A dynamic and kinematic body have collided, one must react.
								float v_length = glm::length(colData.direction);

								//Offset body by depth in other
								if (!anyOfIs(0.f, colData.depth, v_length))
								{
									otherBody->P_position += (colData.depth * (colData.direction / v_length)) * 1.0000001f;

									glm::vec3 normal;
									float normalSize = glm::length(colData.normal);
									normal = colData.normal / normalSize;

									//Adjust velocity
									glm::vec3 withNorm = ((glm::dot(otherBody->P_velocity, colData.normal) / (normalSize * normalSize)) * colData.normal);
									glm::vec3 perpNorm = otherBody->P_velocity - withNorm;
									perpNorm = (1.f - (otherBody->P_friction + kinematicBody->P_friction) / 2 * frictionScalar * dt) * perpNorm;
									//std::cout << perpNorm.x << ',' << (1.f - (otherBody->P_friction + kinematicBody->P_friction) / 2 * frictionScalar * dt) << std::endl;
									otherBody->P_velocity = (withNorm + perpNorm) - withNorm * (1.f + otherBody->P_bounciness);
								}
								if (body1->getGameObject()->getParent())
									otherBody->P_gameObject->localTransform.setPos(otherBody->P_position - (glm::vec3)(otherBody->getGameObject()->getParent()->worldTransform * glm::vec4(VEC3ZERO, 1.0f)));
								else
									otherBody->P_gameObject->localTransform.setPos(otherBody->P_position);
							}
							else
							{

								//THIS DOES NOT TAKE MASS INTO ACCOUNT

								float v_length = glm::length(colData.direction);

								//Offset body by depth in other
								if (!anyOfIs(0.f, colData.depth, v_length))
								{
									glm::vec3 displaceAmount = ((colData.depth * (colData.direction / v_length)) * 1.0000001f) / 2.f;
									body1->P_position += displaceAmount;
									body2->P_position -= displaceAmount;

									glm::vec3 normal;
									float normalSize = glm::length(colData.normal);
									normal = colData.normal / normalSize;

									//Adjust velocity and acceleration so that it stops moving
									glm::vec3 v1 = ((glm::dot(body1->P_velocity, colData.normal) / (normalSize * normalSize)) * colData.normal);
									glm::vec3 v2 = ((glm::dot(body2->P_velocity, colData.normal) / (normalSize * normalSize)) * colData.normal);

									body1->P_velocity -= v1;
									body1->P_velocity += v2;

									body2->P_velocity -= v2;
									body2->P_velocity += v1;
								}
								if (body1->getGameObject()->getParent())
									body1->P_gameObject->localTransform.setPos(body1->P_position - (glm::vec3)(body1->getGameObject()->getParent()->worldTransform * glm::vec4(VEC3ZERO, 1.0f)));
								else
									body1->P_gameObject->localTransform.setPos(body1->P_position);

								if (body1->getGameObject()->getParent())
									body2->P_gameObject->localTransform.setPos(body2->P_position - (glm::vec3)(body2->getGameObject()->getParent()->worldTransform * glm::vec4(VEC3ZERO, 1.0f)));
								else
									body2->P_gameObject->localTransform.setPos(body2->P_position);

								//Two dynamic bodies have collided, both must react
								//float massRatio = body1->getMass() / body2->getMass();

							}
						}
					}

				}

			//Post update
			body1->P_netForce = VEC3ZERO;
		}
	}
}

glm::mat3 P_PhysicsBody::genRotMatrix(glm::vec3 _angles)
{
	glm::mat3 rotX(1.f, 0.f, 0.f,
		0.f, cos(_angles.x), -sin(_angles.x),
		0.f, sin(_angles.x), cos(_angles.x));

	glm::mat3 rotY(cos(_angles.y), 0.f, -sin(_angles.y),
		0.f, 1.f, 0.f,
		sin(_angles.y), 0.f, cos(_angles.y));

	glm::mat3 rotZ(cos(_angles.z), -sin(_angles.z), 0.f,
		sin(_angles.z), cos(_angles.z), 0.f,
		0.f, 0.f, 1.f);

	return (rotZ * rotY) * rotX;
}

void P_PhysicsBody::P_addForce(glm::vec3 newForce)
{
	P_netForce += newForce;
}

void P_PhysicsBody::P_stop()
{
	P_netForce = VEC3ZERO;
	P_acceleration = VEC3ZERO;
	P_velocity = VEC3ZERO;
}

void P_PhysicsBody::drawColliders()
{
	glLineWidth(1.0f);
	for (int i = 0; i < P_bodyCount.size(); i++)
	{
		P_PhysicsBody* currentBody = P_bodyCount[i];
		P_Collider* currentCollider = currentBody->getCollider();
		//Needed for drawing sphere collider, cannot be init in switch
		float num1 = 0.5f;
		float num2 = 0.866f;
		
		//When drawing, the world appears to be on a different scale of points than the glBegin draws
		float scalar = 2.f;
		float offsetX = -0.028f;
		float offsetY = -0.19f;
		float offsetZ = -1.888f;

		float _x = currentBody->P_position.x;
		float _y = currentBody->P_position.y;
		float _z = currentBody->P_position.z;

		float _ox = currentCollider->getOffset().x;
		float _oy = currentCollider->getOffset().y;
		float _oz = currentCollider->getOffset().z;

		float _h = currentCollider->getHeight();
		float _w = currentCollider->getWidth();
		float _d = currentCollider->getDepth();

		switch (currentCollider->getType())
		{
		case BOX:
			//Draw front face
			glBegin(GL_LINE_LOOP);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glEnd();

			//Draw back face
			glBegin(GL_LINE_LOOP);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);
			glEnd();

			//Draw remaining four edges
			glBegin(GL_LINES);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);

			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy + _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);

			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox + _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);

			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz + _d / 2) * scalar + offsetZ);
			glVertex3f((_x + _ox - _w / 2) * scalar + offsetX, (_y + _oy - _h / 2) * scalar + offsetY, (_z + _oz - _d / 2) * scalar + offsetZ);
			glEnd();

			break;
		case SPHERE:
				//X axis circle
				for (int o = -1; o <= 1; o += 2)
				{
					for (int p = -1; p <= 1; p += 2)
					{
						glBegin(GL_LINE_STRIP);
						glVertex3f((_x + _ox + _h * o) * scalar + offsetX,        (_y + _oy) * scalar + offsetY,                 (_z + _oz) * scalar + offsetZ);
						glVertex3f((_x + _ox + _h * o * num2) * scalar + offsetX, (_y + _oy + _h * num1 * p) * scalar + offsetY, (_z + _oz) * scalar + offsetZ);
						glVertex3f((_x + _ox + _h * o * num1) * scalar + offsetX, (_y + _oy + _h * num2 * p) * scalar + offsetY, (_z + _oz) * scalar + offsetZ);
						glVertex3f((_x + _ox) * scalar + offsetX,                 (_y + _oy + _h * p) * scalar + offsetY,        (_z + _oz) * scalar + offsetZ);
						glEnd();
					}
				}

				//Y axis circle
				for (int o = -1; o <= 1; o += 2)
				{
					for (int p = -1; p <= 1; p += 2)
					{
						glBegin(GL_LINE_STRIP);
						glVertex3f((_x + _ox) * scalar + offsetX, (_y + _oy) * scalar + offsetY                , (_z + _oz + _h * o) * scalar + offsetZ);
						glVertex3f((_x + _ox) * scalar + offsetX, (_y + _oy + _h * num1 * p) * scalar + offsetY, (_z + _oz + _h * o * num2) * scalar + offsetZ);
						glVertex3f((_x + _ox) * scalar + offsetX, (_y + _oy + _h * num2 * p) * scalar + offsetY, (_z + _oz + _h * o * num1) * scalar + offsetZ);
						glVertex3f((_x + _ox) * scalar + offsetX, (_y + _oy + _h * p) * scalar + offsetY       , (_z + _oz) * scalar + offsetZ);
						glEnd();
					}
				}

				//Z axis circle
				for (int o = -1; o <= 1; o += 2)
				{
					for (int p = -1; p <= 1; p += 2)
					{
						glBegin(GL_LINE_STRIP);
						glVertex3f((_x + _ox) * scalar + offsetX,                                           (_y + _oy) * scalar + offsetY, (_z + _oz +_h * o) * scalar + offsetZ);
						glVertex3f((_x + _ox + _h * num1 * p) * scalar + offsetX, (_y + _oy) * scalar + offsetY, (_z + _oz +_h * o * num2) * scalar + offsetZ);
						glVertex3f((_x + _ox + _h * num2 * p) * scalar + offsetX, (_y + _oy) * scalar + offsetY, (_z + _oz +_h * o * num1) * scalar + offsetZ);
						glVertex3f((_x + _ox + _h * p) * scalar + offsetX,        (_y + _oy) * scalar + offsetY, (_z + _oz) * scalar + offsetZ);
						glEnd();
					}
				}

			break;
		case CAPSULE:
			//LOL can't draw capsules yet
			//It's just probably gonna be the same thing as sphere but a bit weird-er
			break;
		default:
			break;
		}
	}
}

float P_PhysicsBody::findClosestOnCube(float current, float size)
{

	// Right side of cube
	float tpos = size;
	// Left side of cube
	float tpos2 = -size;

	if (current < tpos2)
		return tpos2;

	else if (current > tpos)
		return tpos;

	//Get % Between min-max
	current += size;

	if (size == 0)
	{
		size = 0.001f;
	}
	current /= (2 * size);

	return Lerp(tpos, tpos2, 1.0f - current);
}

P_CollisionData::P_CollisionData()
{
	didCollide = false;
}

P_CollisionData::P_CollisionData(float _depth, glm::vec3 _direction, glm::vec3 _normal)
{
	didCollide = true;
	depth = _depth;
	direction = _direction;
	normal = _normal;
}
