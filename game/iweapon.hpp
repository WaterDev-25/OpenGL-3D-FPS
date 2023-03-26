#ifndef IWEAPON_HPP
#define IWEAPON_HPP

#include <string>

#include "glshader.hpp"
#include "icamera.hpp"
#include "model.hpp"

class IWeapon
{
public:
	// Constructor
	IWeapon(int damage, std::string model);

	// Destructor
	virtual ~IWeapon() = default;

	// Draw the weapon
	virtual void Draw(CGLShader* shader, ICamera* camera) = 0;

	// Getters
	// Get weapon damage
	int GetDamage();

protected:
	int m_damage;

	CModel* m_pWeapon;
};

#endif // IWEAPON_HPP
