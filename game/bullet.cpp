#include "bullet.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CBullet::CBullet(std::string model, glm::vec3 position, float speed) :
	m_position(position),
	m_speed(speed)
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

	this->m_position.x += this->m_speed * deltaTime;

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
// Purpose: Set bullet position
// ------------------------------------------------------
void CBullet::SetPosition(glm::vec3 position)
{
	this->m_position = position;
}
