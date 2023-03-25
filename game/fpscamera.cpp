#include "fpscamera.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CFPSCamera::CFPSCamera(glm::vec3 position, GLfloat fov, GLfloat yaw, GLfloat pitch) :
	m_position(position),
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_right(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_yaw(yaw),
	m_pitch(pitch),
	m_fov(fov)
{
	this->UpdateCameraVectors();
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CFPSCamera::~CFPSCamera()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Return the view matrix
// ------------------------------------------------------
glm::mat4 CFPSCamera::GetViewMatrix()
{
	return glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

// ------------------------------------------------------
// Purpose: Return the camera position
// ------------------------------------------------------
glm::vec3 CFPSCamera::GetPosition()
{
	return this->m_position;
}

// ------------------------------------------------------
// Purpose: Return the camera front
// ------------------------------------------------------
glm::vec3 CFPSCamera::GetFront()
{
	return this->m_front;
}

// ------------------------------------------------------
// Purpose: Return the camera right
// ------------------------------------------------------
glm::vec3 CFPSCamera::GetRight()
{
	return this->m_right;
}

// ------------------------------------------------------
// Purpose: Return the camera up
// ------------------------------------------------------
glm::vec3 CFPSCamera::GetUp()
{
	return this->m_up;
}

// ------------------------------------------------------
// Purpose: Return the camera yaw
// ------------------------------------------------------
GLfloat CFPSCamera::GetYaw()
{
	return this->m_yaw;
}

// ------------------------------------------------------
// Purpose: Return the camera pitch
// ------------------------------------------------------
GLfloat CFPSCamera::GetPitch()
{
	return this->m_pitch;
}

// ------------------------------------------------------
// Purpose: Return the camera field of view
// ------------------------------------------------------
GLfloat CFPSCamera::GetFov()
{
	return this->m_fov;
}

// ------------------------------------------------------
// Purpose: Set camera position
// ------------------------------------------------------
void CFPSCamera::SetPosition(glm::vec3 position)
{
	this->m_position = position;
}

// ------------------------------------------------------
// Purpose: Set camera yaw
// ------------------------------------------------------
void CFPSCamera::SetYaw(GLfloat yaw)
{
	this->m_yaw = yaw;
}

// ------------------------------------------------------
// Purpose: Set camera pitch
// ------------------------------------------------------
void CFPSCamera::SetPitch(GLfloat pitch)
{
	this->m_pitch = pitch;
}

// ------------------------------------------------------
// Purpose: Calculates the front vector from the camera
// ------------------------------------------------------
void CFPSCamera::UpdateCameraVectors()
{
	// Calculate the new front vector
	glm::vec3 front = glm::vec3(
		cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch)),
		sin(glm::radians(this->m_pitch)),
		sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch))
	);

	this->m_front = glm::normalize(front);

	// Re-calculate the right and up vector
	this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
	this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}
