#ifndef BULLET_HPP
#define BULLET_HPP

#include "glshader.hpp"
#include "model.hpp"

#include <glm/glm.hpp>

class CBullet
{
public:
	// Constructor
	CBullet(std::string model, glm::vec3 position, float speed);

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

	glm::vec3 m_position;

	float m_speed;
};

#endif // BULLET_HPP
