#include "StdAfx.h"
#include "LevelUpgradeVisitor.h"
#include "Modifiable.h"
#include "Player.h"
#include "Shotgun.h"
#include "MagicWand.h"
#include <iostream>

LevelUpgradeVisitor::LevelUpgradeVisitor(void)
{
}


LevelUpgradeVisitor::~LevelUpgradeVisitor(void)
{
}

void LevelUpgradeVisitor::visit(Modifiable* visitable)
{
	// determine what visitable is and then pass to the correct upgrade function
	// hint: dynamic_cast
}

void LevelUpgradeVisitor::upgrade(Player& p) 
{
}

void LevelUpgradeVisitor::upgrade(Shotgun& s)
{
}

void LevelUpgradeVisitor::upgrade(MagicWand& w)
{
}
