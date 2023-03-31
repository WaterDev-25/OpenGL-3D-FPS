#include "player.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CPlayer::CPlayer(glm::vec3 position, glm::vec3 gravity, CDebug* debug, CMap* map, CPhysics* physics) :
	m_aabb(SPlayer{ position, glm::vec3(0.0f), glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f) }),
	m_gravity(gravity),
	m_speed(3.5f),
	m_mouseSensitivity(0.1f),
	m_jumpForce(5.0f),
	m_keys(SDL_GetKeyboardState(NULL)),
	m_firstMouse(true),
	m_isJumping(false),
	m_isGrounded(false),
	m_isFiring(false),
	m_pDebug(debug),
	m_pMap(map),
	m_pPhysics(physics)
{
	this->m_pCamera = new CFPSCamera(this->m_aabb.position + this->m_aabb.size, 75.0f);

	this->m_pCamera->UpdateCameraVectors();

	this->m_pWeapon = new CWeaponGlock();

	// Debugs messages
	this->m_pDebug->AddInfo("Velocity: " + std::to_string(this->m_aabb.velocity.x) + ", " + std::to_string(this->m_aabb.velocity.y) + ", " + std::to_string(this->m_aabb.velocity.z));
	this->m_pDebug->AddInfo("Position: " + std::to_string(this->m_aabb.position.x) + ", " + std::to_string(this->m_aabb.position.y) + ", " + std::to_string(this->m_aabb.position.z));
	this->m_pDebug->AddInfo("Last position: " + std::to_string(this->m_aabb.lastPosition.x) + ", " + std::to_string(this->m_aabb.lastPosition.y) + ", " + std::to_string(this->m_aabb.lastPosition.z));
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CPlayer::~CPlayer()
{
	// RAII
	delete this->m_pCamera;
	delete this->m_pWeapon;
	this->m_keys = nullptr;

	for (auto& bullet : this->m_bullets)
		delete bullet;
}

// ------------------------------------------------------
// Purpose: Player update
// ------------------------------------------------------
void CPlayer::Update(float deltaTime)
{
	this->m_pCamera->SetPosition(this->m_aabb.position + this->m_aabb.size);

	// Player movement
	if (this->m_keys[SDL_SCANCODE_W])
		ProcessKeyboard(FORWARD, deltaTime);
	if (this->m_keys[SDL_SCANCODE_A])
		ProcessKeyboard(LEFT, deltaTime);
	if (this->m_keys[SDL_SCANCODE_S])
		ProcessKeyboard(BACKWARD, deltaTime);
	if (this->m_keys[SDL_SCANCODE_D])
		ProcessKeyboard(RIGHT, deltaTime);
	if (this->m_keys[SDL_SCANCODE_SPACE] && !this->m_isJumping)
		ProcessKeyboard(JUMP, deltaTime);

	// Player mouse movement
	this->HandleMouseMovement();

	// Apply gravity
	glm::vec3 gravity = this->m_gravity;
	this->m_aabb.velocity += gravity * deltaTime;
	this->m_aabb.position += this->m_aabb.velocity * deltaTime;

	// Handle jump
	this->HandleJump();

	// Handle collision (AABB)
	this->HandleCollision();

	// Debugs messages
	this->m_pDebug->EditInfo(0, "Velocity: " + std::to_string(this->m_aabb.velocity.x) + ", " + std::to_string(this->m_aabb.velocity.y) + ", " + std::to_string(this->m_aabb.velocity.z));
	this->m_pDebug->EditInfo(1, "Position: " + std::to_string(this->m_aabb.position.x) + ", " + std::to_string(this->m_aabb.position.y) + ", " + std::to_string(this->m_aabb.position.z));
	this->m_pDebug->EditInfo(2, "Last position: " + std::to_string(this->m_aabb.lastPosition.x) + ", " + std::to_string(this->m_aabb.lastPosition.y) + ", " + std::to_string(this->m_aabb.lastPosition.z));
}

// ------------------------------------------------------
// Purpose: Player input event
// ------------------------------------------------------
void CPlayer::InputEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		// Fire
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if (!this->m_isFiring)
				this->Fire();
		}
	}
}

// ------------------------------------------------------
// Purpose: Render the current weapon
// ------------------------------------------------------
void CPlayer::RenderWeapon(CGLShader* shader)
{
	this->m_pWeapon->Draw(shader, this->m_pCamera);
}

// ------------------------------------------------------
// Purpose: Weapon fire
// ------------------------------------------------------
void CPlayer::Fire()
{
	this->m_isFiring = true;

	if(this->m_isFiring)
		this->m_bullets.push_back(new CBullet("res/models/guns/bullet/bullet.obj", this->m_pCamera->GetPosition(), 5.0f, this->m_pCamera->GetFront()));

	this->m_isFiring = false;
}

void CPlayer::RenderBullets(CGLShader* shader, float deltaTime)
{
	for (auto& bullet : this->m_bullets)
		bullet->Render(shader, deltaTime);
}

// ------------------------------------------------------
// Purpose: Return the player position
// ------------------------------------------------------
glm::vec3 CPlayer::GetPosition()
{
	return this->m_aabb.position;
}

// ------------------------------------------------------
// Purpose: Return the camera
// ------------------------------------------------------
ICamera* CPlayer::GetCamera()
{
	return this->m_pCamera;
}

// ------------------------------------------------------
// Purpose: Process input received from keyboard
// ------------------------------------------------------
void CPlayer::ProcessKeyboard(ECameraMovement direction, float deltaTime)
{
	switch (direction)
	{
	case FORWARD:
		if (this->m_isJumping)
			this->m_aabb.velocity += glm::normalize(glm::vec3(glm::cos(glm::radians(this->m_pCamera->GetYaw())), 0, glm::sin(glm::radians(this->m_pCamera->GetYaw())))) * this->m_speed * deltaTime;
		else
		{
			this->m_aabb.velocity = glm::normalize(glm::vec3(glm::cos(glm::radians(this->m_pCamera->GetYaw())), 0, glm::sin(glm::radians(this->m_pCamera->GetYaw())))) * this->m_speed * deltaTime;
			this->m_aabb.position += this->m_aabb.velocity;
		}
		break;
	case LEFT:
		if (this->m_isJumping)
			this->m_aabb.velocity -= glm::normalize(this->m_pCamera->GetRight()) * this->m_speed * deltaTime;
		else
		{
			this->m_aabb.velocity = glm::normalize(this->m_pCamera->GetRight()) * this->m_speed * deltaTime;
			this->m_aabb.position -= this->m_aabb.velocity;
		}
		break;
	case BACKWARD:
		if (this->m_isJumping)
			this->m_aabb.velocity -= glm::normalize(glm::vec3(glm::cos(glm::radians(this->m_pCamera->GetYaw())), 0, glm::sin(glm::radians(this->m_pCamera->GetYaw())))) * this->m_speed * deltaTime;
		else
		{
			this->m_aabb.velocity = glm::normalize(glm::vec3(glm::cos(glm::radians(this->m_pCamera->GetYaw())), 0, glm::sin(glm::radians(this->m_pCamera->GetYaw())))) * this->m_speed * deltaTime;
			this->m_aabb.position -= this->m_aabb.velocity;
		}
		break;
	case RIGHT:
		if (this->m_isJumping)
			this->m_aabb.velocity += glm::normalize(this->m_pCamera->GetRight()) * this->m_speed * deltaTime;
		else
		{
			this->m_aabb.velocity = glm::normalize(this->m_pCamera->GetRight()) * this->m_speed * deltaTime;
			this->m_aabb.position += this->m_aabb.velocity;
		}
		break;
	case JUMP:
		if (!this->m_isJumping)
		{
			this->m_aabb.velocity.y = this->m_jumpForce;
			this->m_isJumping = true;
		}
		break;
	default:
		break;
	}
}

// ------------------------------------------------------
// Purpose: Handle jump
// ------------------------------------------------------
void CPlayer::HandleJump()
{
	if (this->m_isGrounded)
	{
		//this->m_aabb.velocity.y = 0.0f;
		// -- debug
		this->m_aabb.velocity = glm::vec3(0.0f);
		this->m_isJumping = false;
	}
}

// ------------------------------------------------------
// Purpose: Process input received from mouse
// ------------------------------------------------------
void CPlayer::HandleMouseMovement(GLboolean constrainPitch)
{
	int x = 0;
	int y = 0;

	float lastx = 0;
	float lasty = 0;

	SDL_GetRelativeMouseState(&x, &y);

	if (this->m_firstMouse)
	{
		lastx = (float)x;
		lasty = (float)y;

		this->m_firstMouse = false;
	}

	float xoffset = x - lastx;
	float yoffset = lasty - y;

	lastx = (float)x;
	lasty = (float)y;

	xoffset *= this->m_mouseSensitivity;
	yoffset *= this->m_mouseSensitivity;

	this->m_pCamera->SetYaw(this->m_pCamera->GetYaw() + xoffset);
	this->m_pCamera->SetPitch(this->m_pCamera->GetPitch() + yoffset);

	if (constrainPitch)
	{
		if (this->m_pCamera->GetPitch() > 89.0f)
			this->m_pCamera->SetPitch(89.0f);
		if (this->m_pCamera->GetPitch() < -89.0f)
			this->m_pCamera->SetPitch(-89.0f);
	}

	this->m_pCamera->UpdateCameraVectors();
}

// ------------------------------------------------------
// Purpose: Check collision
// ------------------------------------------------------
void CPlayer::HandleCollision()
{
	// -- debug
	bool done = false;

	for (int i = 0; i < this->m_pMap->GetAABBS().size(); i++)
	{
		SPlayerToBoxCollision collision = this->m_pPhysics->AABBCollision(this->m_aabb, this->m_pMap->GetAABBS()[i]);

		if (collision.collision)
		{
			if (collision.box.axis.x == 1.0f)
				this->m_aabb.position.x = this->m_aabb.lastPosition.x;

			if (collision.box.axis.y == 1.0f)
			{
				this->m_aabb.position.y = this->m_aabb.lastPosition.y;

				done = true;
			}

			if (collision.box.axis.z == 1.0f)
				this->m_aabb.position.z = this->m_aabb.lastPosition.z;
		}
	}

	if(done)
		this->m_isGrounded = true;
	else
		this->m_isGrounded = false;

	this->m_aabb.lastPosition = this->m_aabb.position;
}
