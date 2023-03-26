#include "iweapon.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
IWeapon::IWeapon(int damage, std::string model) :
	m_damage(damage)
{
	this->m_pWeapon = new CModel(model);
}

// ------------------------------------------------------
// Purpose: Get weapon damage
// ------------------------------------------------------
int IWeapon::GetDamage()
{
	return this->m_damage;
}
