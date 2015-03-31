#pragma once

#include "Weapon.h"

class MagicWand : public Weapon
{
public:
	MagicWand(void);
	MagicWand(const MagicWand& w);
	~MagicWand(void);

	MagicWand& operator=(const MagicWand& w);

	inline void setPowerLevel(int level) {m_powerLevel = level;}
	inline int getPowerLevel() {return m_powerLevel;}

	void primaryAttack();
	void secondaryAttack();

	void letsModify(Visitor* visitor);

private:
	int m_powerLevel;
};

