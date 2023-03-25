#ifndef FPSCAMERA_HPP
#define FPSCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "icamera.hpp"

class CFPSCamera : public ICamera
{
public:
	// Constructor
	CFPSCamera(glm::vec3 position, GLfloat fov = 45.0f, GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);

	// Destructor
	~CFPSCamera() override;

	// Getters
	// Return the view matrix
	glm::mat4 GetViewMatrix() final;

	// Return the camera position
	glm::vec3 GetPosition() final;

	// Return the camera front
	glm::vec3 GetFront() final;

	// Return the camera right
	glm::vec3 GetRight() final;

	// Return the camera up
	glm::vec3 GetUp() final;

	// Return the camera yaw
	GLfloat GetYaw() final;

	// Return the camera pitch
	GLfloat GetPitch() final;

	// Return the camera field of view
	GLfloat GetFov() final;

	// Setters
	// Set camera position
	void SetPosition(glm::vec3 position) final;

	// Set camera yaw
	void SetYaw(GLfloat yaw) final;

	// Set camera pitch
	void SetPitch(GLfloat pitch) final;

	// Calculates the front vector from the camera
	void UpdateCameraVectors() final;

private:
	// FPS camera data
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_worldUp;
	
	// Euler angles
	GLfloat m_yaw;
	GLfloat m_pitch;

	GLfloat m_fov;
};

#endif // FPSCAMERA_HPP
