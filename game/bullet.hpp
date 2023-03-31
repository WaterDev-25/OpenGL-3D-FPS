#ifndef BULLET_HPP
#define BULLET_HPP

#include "glshader.hpp"
#include "model.hpp"
#include "physics.hpp"
#include "icamera.hpp"

#include <glm/glm.hpp>

class CBullet
{
public:
	// Constructor
	CBullet(std::string model, glm::vec3 position, float speed, glm::vec3 cameraFront);

	// Destructor
	~CBullet();

	// Render bullet with physics
	void Render(CGLShader* shader, float deltaTime);

	// Getters
	// Get bullet position
	glm::vec3 GetPosition();

	// Get bullet speed
	float GetSpeed();

	// Setters
	// Set bullet position
	void SetPosition(glm::vec3 position);

	// Set bullet speed
	void SetSpeed(float speed);

private:
	CModel* m_pModel;

	SSphere m_sphere;

	glm::vec3 m_position;
	glm::vec3 m_velocity;

	float m_speed;

	glm::vec3 m_cameraFront;
};

#endif // BULLET_HPP
