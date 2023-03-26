#include "weapon_glock.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CWeaponGlock::CWeaponGlock() :
	IWeapon(10, "res/weapons/glock/glock.obj")
{
	// --
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CWeaponGlock::~CWeaponGlock()
{
	// RAII
	delete this->m_pWeapon;
}

// ------------------------------------------------------
// Purpose: Draw the weapon
// ------------------------------------------------------
void CWeaponGlock::Draw(CGLShader* shader, ICamera* camera)
{
	// Init the transform matrix
	glm::mat4 model = glm::mat4(1.0f);

	glm::vec3 weaponOffset = glm::vec3(-0.2f, -0.4f, 0.5f);
	glm::vec3 gunPosition = glm::vec3(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	model = glm::translate(model, gunPosition);
	model = glm::rotate(model, -glm::radians(camera->GetYaw() - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, -glm::radians(camera->GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	// Calculate the position of the weapon relative to the gun
	glm::vec3 weaponOffsetVec = weaponOffset;
	glm::vec4 weaponOffsetWorld = model * glm::vec4(weaponOffsetVec, 1.0f);

	// Translate the weapon to the correct position relative to the gun
	glm::mat4 weaponModel = glm::mat4(1.0f);
	weaponModel = glm::translate(weaponModel, glm::vec3(weaponOffsetWorld));
	weaponModel = glm::rotate(weaponModel, -glm::radians(camera->GetYaw() - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	weaponModel = glm::rotate(weaponModel, -glm::radians(camera->GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	shader->SetMat4("model", weaponModel);

	this->m_pWeapon->Draw(shader);
}
