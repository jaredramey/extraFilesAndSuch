#pragma once

#include "Modifiable.h"

class Weapon : public Modifiable
{
public:

	virtual void primaryAttack() = 0;
	virtual void secondaryAttack() = 0;
};

