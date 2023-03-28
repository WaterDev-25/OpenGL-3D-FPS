#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "fpscamera.hpp"
#include "map.hpp"
#include "physics.hpp"
#include "glshader.hpp"
#include "model.hpp"
#include "debug.hpp"
#include "weapon_glock.hpp"
#include "bullet.hpp"

enum ECameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	JUMP
};

class CPlayer
{
public:
	// Constructor
	CPlayer(glm::vec3 position, CDebug* debug, CMap* map, CPhysics* physics);

	// Destructor
	~CPlayer();

	// Player update
	void Update(float deltaTime);

	// Player input event
	void InputEvent(SDL_Event* e);

	// Render the current weapon
	void RenderWeapon(CGLShader* shader);

	// Weapon fire
	void Fire();
	
	// Render bullets
	void RenderBullets(CGLShader* shader, float deltaTime);

	// Setters
	// Return the player position
	glm::vec3 GetPosition();

	// Return the camera
	ICamera* GetCamera();

private:
	// Player attributes
	SPlayer m_aabb;

	ICamera* m_pCamera;

	IWeapon* m_pWeapon;

	std::vector<CBullet*> m_bullets;

	// Player options
	GLfloat m_speed;
	GLfloat m_mouseSensitivity;
	GLfloat m_jumpForce;

	// Keyboard key state
	const uint8_t* m_keys;

	bool m_firstMouse;
	bool m_isJumping;
	bool m_isGrounded;
	bool m_isFiring;

	CDebug* m_pDebug;
	CMap* m_pMap;
	CPhysics* m_pPhysics;

	// Process input received from keyboard
	void ProcessKeyboard(ECameraMovement direction, float deltaTime);

	// Handle input received from mouse
	void HandleMouseMovement(GLboolean constrainPitch = true);

	// Handle collision
	void HandleCollision();

	// Handle jump
	void HandleJump();
};

#endif // PLAYER_HPP
