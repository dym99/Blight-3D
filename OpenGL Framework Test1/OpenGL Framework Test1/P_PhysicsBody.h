#ifndef _P_PHYSICS_BODY_H_
#define _P_PHYSICS_BODY_H_
#define P_GRAVITY -9.8f
#define VEC3ZERO glm::vec3(0, 0, 0)

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "P_Collider.h"
#include "Transform.h"
#include "MathFunc.h"
#include <math.h>

struct P_RayData
{
	P_RayData();
	bool didCollide;
	float depth;
	glm::vec3 intersection;

};

struct P_CollisionData
{
public:
	P_CollisionData();
	P_CollisionData(float _depth, glm::vec3 _direction, glm::vec3 _normal);

	bool didCollide;
	float depth;
	glm::vec3 direction;
	glm::vec3 normal;
};

class P_PhysicsBody
{
public:
	P_PhysicsBody();
	P_PhysicsBody(Transform* _transform, float _mass, bool _gravity, P_Collider_Type _type, float _h, float _w = 1.0f, float _d = 1.0f, glm::vec3 _offset = glm::vec3(0, 0, 0), float _bounciness = 0.0f, float _friction = 0.0f, bool _kinematic = false);
	P_PhysicsBody(Transform* _transform, float _mass, bool _gravity, bool _kinematic = false);
	~P_PhysicsBody();

	//Rudimentary collision check that uses bounding spheres. This is soon to be changed to probably AABB
	static P_CollisionData P_checkBounds(int i, int o);
	//Refined collision check that uses the proper defined collision shape.
	static P_CollisionData P_checkCollision(int i, int o);

	//Should be called every frame
	static void P_physicsUpdate(float dt);

	//This is a ease of use function that returns true if the operand is equal to any of the provided values, regardless of how many there are.
	//Can be used to check if any values are zero before dividing, etc.
	template<typename T, typename... Args>
	static bool anyOfIs(T operand, T val, Args... args);
	template<typename T>
	static bool anyOfIs(T operand, T val);

	//Ditto above, but searches for data that is *not* the given value
	template<typename T, typename... Args>
	static bool anyOfIsNot(T operand, T val, Args... args);
	template<typename T>
	static bool anyOfIsNot(T operand, T val);

	static glm::mat3 genRotMatrix(glm::vec3 _angles);

	static std::vector<P_PhysicsBody*> P_bodyCount;

	float getMass() { return P_mass; }
	P_Collider* getCollider() { return P_collider; }
	void setTransform(Transform* _transform) { P_transform = _transform; P_position = _transform->getPos(); }

	void P_addForce(glm::vec3 newForce);
	void P_stop();

	static void drawColliders();
	static float findClosestOnCube(float current, float size);
private:
	//Physic-al Values (get it? Ba-dum Tss!)
	float P_mass;
	float P_bounciness; // Try to keep between 0 and 1 or some weird stuff will happen. Unless you want that. Idc, I'm not the boss of you.
	float P_friction; //Technically not the frictional coefficiant, but I'd have to rewrite a lot of stuff to use the actual frictional equation.
						//0 is super slidy, 1 is sticky as heck, ie. stops all movement perpendicular to the normal when pressed into
	glm::vec3 P_netForce;
	glm::vec3 P_acceleration = VEC3ZERO;
	glm::vec3 P_velocity = VEC3ZERO;
	glm::vec3 P_position = VEC3ZERO;

	bool P_useGravity = false;
	bool P_isKinematic = false;

	P_Collider* P_collider;

	Transform* P_transform;
	glm::vec3 startPos;
};

#endif // !_P_PHYSICS_BODY_H_

template<typename T, typename ...Args>
inline bool P_PhysicsBody::anyOfIs(T operand, T val, Args ...args)
{
	return (0 != ((operand == val) + anyOfIs(operand, args...)));
}

template<typename T>
inline bool P_PhysicsBody::anyOfIs(T operand, T val)
{
	return operand == val;
}

template<typename T, typename ...Args>
inline bool P_PhysicsBody::anyOfIsNot(T operand, T val, Args ...args)
{
	return false;
}

template<typename T>
inline bool P_PhysicsBody::anyOfIsNot(T operand, T val)
{
	return false;
}
