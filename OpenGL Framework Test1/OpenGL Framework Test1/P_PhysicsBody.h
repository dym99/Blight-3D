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

enum P_FlagType
{
	F_DEFAULT,
	F_ENEMY,
	F_PLAYER,
	F_ENVIRONMENT
};

struct P_RayData
{
	P_RayData();
	bool didCollide;
	float distance;
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
	P_PhysicsBody(Transform* _transform, float _mass, bool _gravity, P_Collider_Type _type, float _h, float _w = 1.0f, float _d = 1.0f, glm::vec3 _offset = glm::vec3(0, 0, 0), float _bounciness = 0.0f, float _friction = 0.0f, bool _kinematic = false, bool _trigger = false, P_FlagType _flag = F_DEFAULT);
	P_PhysicsBody(Transform* _transform, float _mass, bool _gravity, bool _kinematic = false);
	~P_PhysicsBody();

	//Rudimentary collision check that uses bounding spheres. This is soon to be changed to probably AABB
	static P_CollisionData P_checkBounds(int i, int o);
	//Refined collision check that uses the proper defined collision shape
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

	//All physics bodies
	static std::vector<P_PhysicsBody*> P_bodyCount;

	//Getters and setters
	void setMass(float _mass) { P_mass = _mass; }
	float getMass() { return P_mass; }
	void setBounce(float _bounciness) { P_bounciness = _bounciness; }
	float getBounce() { return P_bounciness;  }
	void setFriction(float _friction) { P_friction = _friction; }
	float getFriction() { return P_friction; }
	P_Collider* getCollider() { return P_collider; }
	void setTransform(Transform* _transform) { P_transform = _transform; P_position = _transform->getPos(); }
	//Only call after physics update
	bool get_triggered() { return P_triggered; }

	void giveFlag(P_FlagType _newFlag) { P_flags.push_back(_newFlag); }
	void removeFlags() { P_flags.clear(); }
	void ignoreFlag(P_FlagType _ignFlag) { P_flagsToIgnore.push_back(_ignFlag); }
	void removeIgnFlags() { P_flagsToIgnore.clear(); }
	void flagWhitelist() { P_whitelist = true; }
	void flagBlacklist() { P_whitelist = false; }

	void P_addForce(glm::vec3 newForce);
	void P_stop();


	static void drawColliders();
	static float findClosestOnCube(float current, float size);
private:
	//Ignore flags. When an object attempts to collide with another flagged with a flag that matches one from the ignore list, the collision test is not performed
	//Thus, the objects pass through eachother
	std::vector<P_FlagType> P_flags;
	std::vector<P_FlagType> P_flagsToIgnore;
	bool P_whitelist = false;				  // Should the computer treat these flags as a whitelist or blacklist? DM me if you don't know the difference. 
											  // false = blacklist, true = whitelist

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

	/*Trigger Objects*/
	/*
	  Trigger objects behave similarly to non-trigger objects
	  The main difference being that a trigger object does not react when collided with
	  They pass through everything, and anything may pass through them
	  Similar to non-trigger objects, a trigger can have flags white/blacklisted for it
	  Instead of not colliding with these flagged objects, they will/will-not tigger the trigger object
	  An object not tagged as a trigger can still have trigger data retrieved, however, it will still collide with the surrounding objects
	  DM me for more information or clarifacation! ~Spratley ;)
	*/
	bool P_isTrigger = false; 
	bool P_triggered = false;

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
