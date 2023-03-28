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

	// Setters
	// Set bullet position
	void SetPosition(glm::vec3 position);

private:
	CModel* m_pModel;

	glm::vec3 m_position;

	float m_speed;
};

#endif // BULLET_HPP
