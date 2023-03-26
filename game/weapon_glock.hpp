#ifndef WEAPON_GLOCK
#define WEAPON_GLOCK

#include "iweapon.hpp"
#include "icamera.hpp"

#include <glm/glm.hpp>

class CWeaponGlock : public IWeapon
{
public:
	// Constructor
	CWeaponGlock();

	// Destructor
	~CWeaponGlock() override;

	// Draw the weapon
	void Draw(CGLShader* shader, ICamera* camera) final;
};

#endif // WEAPON_GLOCK
