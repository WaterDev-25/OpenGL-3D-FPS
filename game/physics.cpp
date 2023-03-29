#include "physics.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CPhysics::CPhysics()
{
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CPhysics::~CPhysics()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Detect AABB collision on a point
// ------------------------------------------------------
SPointCollision CPhysics::AABBCollision(glm::vec3& position, SAABB& box)
{
	SPointCollision collision;

	if (position.x >= box.position.x
		&& position.x < box.position.x + box.size.x
		&& position.y >= box.position.y
		&& position.y < box.position.y + box.size.y
		&& position.z >= box.position.z
		&& position.z < box.position.z + box.size.z)
		collision.collision = true;
	else
		collision.collision = false;

	collision.position = position;
	collision.box = box;

	return collision;
}

// ------------------------------------------------------
// Purpose: Detect AABB collision
// ------------------------------------------------------
SBoxToBoxCollision CPhysics::AABBCollision(SAABB& box1, SAABB& box2)
{
	SBoxToBoxCollision collision;

	if ((box2.position.x >= box1.position.x + box1.size.x)
		|| (box2.position.x + box2.size.x <= box1.position.x)
		|| (box2.position.y >= box1.position.y + box1.size.y)
		|| (box2.position.y + box2.size.y <= box1.position.y)
		|| (box2.position.z >= box1.position.z + box1.size.z)
		|| (box2.position.z + box2.size.z <= box1.position.z))
		collision.collision = false;
	else
		collision.collision = true;

	collision.box1 = box1;
	collision.box2 = box2;

	return collision;
}

// ------------------------------------------------------
// Purpose: Detect AABB collision between player and box
// ------------------------------------------------------
SPlayerToBoxCollision CPhysics::AABBCollision(SPlayer& player, SAABB& box)
{
	SPlayerToBoxCollision collision;

	if ((box.position.x >= player.position.x + player.size.x)
		|| (box.position.x + box.size.x <= player.position.x)
		|| (box.position.y >= player.position.y + player.size.y)
		|| (box.position.y + box.size.y <= player.position.y)
		|| (box.position.z >= player.position.z + player.size.z)
		|| (box.position.z + box.size.z <= player.position.z))
		collision.collision = false;
	else
		collision.collision = true;

	collision.player = player;
	collision.box = box;

	return collision;
}

// ------------------------------------------------------
// Purpose: Detect Sphere collision on a point
// ------------------------------------------------------
SPointToSphereCollision CPhysics::SphereCollision(glm::vec3& position, SSphere& sphere)
{
	SPointToSphereCollision collision;

	int d2 = (int)(position.x - sphere.position.x) * (int)(position.x - sphere.position.x) + (int)(position.x - sphere.position.x) * (int)(position.y - sphere.position.y) + (int)(position.z - sphere.position.z) * (int)(position.z - sphere.position.z);
	if (d2 > sphere.radius * sphere.radius)
		collision.collision = false;
	else
		collision.collision = true;

	collision.position = position;
	collision.sphere = sphere;

	return collision;
}

// ------------------------------------------------------
// Purpose: Detect Sphere collision
// ------------------------------------------------------
SSphereToSphereCollision CPhysics::SphereCollision(SSphere& sphere1, SSphere& sphere2)
{
	SSphereToSphereCollision collision;

	int d2 = (int)(sphere1.position.x - sphere2.position.x) * (int)(sphere1.position.x - sphere2.position.x) + (int)(sphere1.position.x - sphere2.position.x) * (int)(sphere1.position.y - sphere2.position.y) + (int)(sphere1.position.z - sphere2.position.z) * (int)(sphere1.position.z - sphere2.position.z);
	if (d2 > (sphere1.radius + sphere2.radius) * (sphere1.radius + sphere2.radius))
		collision.collision = false;
	else
		collision.collision = true;

	collision.sphere1 = sphere1;
	collision.sphere2 = sphere2;

	return collision;
}
