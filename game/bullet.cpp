#include "bullet.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CBullet::CBullet(std::string model, glm::vec3 position, float speed, glm::vec3 cameraFront) :
	m_position(position),
	m_velocity(glm::vec3(0.0f)),
	m_speed(speed),
	m_cameraFront(cameraFront),
	m_sphere(SSphere { position, 2.0f })
{
	// Init bullet model
	this->m_pModel = new CModel(model);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CBullet::~CBullet()
{
	// RAII
	delete this->m_pModel;
}

// ------------------------------------------------------
// Purpose: Render bullet with physics
// ------------------------------------------------------
void CBullet::Render(CGLShader* shader, float deltaTime)
{
	glm::mat4 model = glm::mat4(1.0f);

	glm::vec3 direction = glm::normalize(this->m_cameraFront);

	this->m_velocity = direction * this->m_speed;
	this->m_position += this->m_velocity * deltaTime;

	model = glm::translate(model, this->m_position);
	model = glm::scale(model, glm::vec3(0.1f));

	shader->SetMat4("model", model);

	this->m_pModel->Draw(shader);
}

// ------------------------------------------------------
// Purpose: Get bullet position
// ------------------------------------------------------
glm::vec3 CBullet::GetPosition()
{
	return this->m_position;
}

// ------------------------------------------------------
// Purpose: Get bullet speed
// ------------------------------------------------------
float CBullet::GetSpeed()
{
	return this->m_speed;
}

// ------------------------------------------------------
// Purpose: Set bullet position
// ------------------------------------------------------
void CBullet::SetPosition(glm::vec3 position)
{
	this->m_position = position;
}

// ------------------------------------------------------
// Purpose: Set bullet position
// ------------------------------------------------------
void CBullet::SetSpeed(float speed)
{
	this->m_speed = speed;
}
