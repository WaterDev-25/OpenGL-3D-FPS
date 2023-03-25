#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

class ICamera
{
public:
	// Destructor
	virtual ~ICamera() = default;

	// Getters
	// Return the view matrix
	virtual glm::mat4 GetViewMatrix() = 0;

	// Return the camera position
	virtual glm::vec3 GetPosition() = 0;

	// Return the camera front
	virtual glm::vec3 GetFront() = 0;

	// Return the camera right
	virtual glm::vec3 GetRight() = 0;

	// Return the camera up
	virtual glm::vec3 GetUp() = 0;

	// Return the camera yaw
	virtual GLfloat GetYaw() = 0;

	// Return the camera pitch
	virtual GLfloat GetPitch() = 0;

	// Return the camera field of view
	virtual GLfloat GetFov() = 0;

	// Setters
	// Set camera position
	virtual void SetPosition(glm::vec3 position) = 0;

	// Set camera yaw
	virtual void SetYaw(GLfloat yaw) = 0;

	// Set camera pitch
	virtual void SetPitch(GLfloat pitch) = 0;

	// Calculates the front vector from the camera
	virtual void UpdateCameraVectors() = 0;
};

#endif // CAMERA_HPP
