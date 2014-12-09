#pragma once

#include "Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun(void);
	Shotgun(const Shotgun& s);
	~Shotgun(void);

	Shotgun& operator=(const Shotgun& s);

	inline void setDualShotgunEnabled(bool state) {m_bIsDualShotgunEnabled = state;}
	inline bool isDualShotgunEnabled() {return m_bIsDualShotgunEnabled;}

	void primaryAttack();
	void secondaryAttack();

	void letsModify(Visitor* visitor);

private:
	bool m_bIsDualShotgunEnabled;
};

