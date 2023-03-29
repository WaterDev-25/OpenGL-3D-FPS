#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <glm/glm.hpp>

#include <algorithm>

struct SAABB
{
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 axis;
};

struct SSphere
{
	glm::vec3 position;

	float radius;
};

struct SPlayer
{
	glm::vec3 position;
	glm::vec3 lastPosition;
	glm::vec3 size;
	glm::vec3 axis;
	glm::vec3 velocity;
};

struct SPointCollision
{
	glm::vec3 position;
	SAABB box;

	bool collision;
};

struct SBoxToBoxCollision
{
	SAABB box1;
	SAABB box2;

	bool collision;
};

struct SPlayerToBoxCollision
{
	SPlayer player;
	SAABB box;

	bool collision;
};

struct SPointToSphereCollision
{
	glm::vec3 position;
	SSphere sphere;

	bool collision;
};

struct SSphereToSphereCollision
{
	SSphere sphere1;
	SSphere sphere2;

	bool collision;
};

class CPhysics
{
public:
	// Constructor
	CPhysics();

	// Destructor
	~CPhysics();

	// Detect AABB collision on a point
	SPointCollision AABBCollision(glm::vec3& position, SAABB& box);

	// Detect AABB collision
	SBoxToBoxCollision AABBCollision(SAABB& box1, SAABB& box2);

	// Detect AABB collision between player and box
	SPlayerToBoxCollision AABBCollision(SPlayer& player, SAABB& box);

	// Detect Sphere collision on a point
	SPointToSphereCollision SphereCollision(glm::vec3& position, SSphere& sphere);

	// Detect Sphere collision
	SSphereToSphereCollision SphereCollision(SSphere& sphere1, SSphere& sphere2);
};

#endif // PHYSICS_HPP
