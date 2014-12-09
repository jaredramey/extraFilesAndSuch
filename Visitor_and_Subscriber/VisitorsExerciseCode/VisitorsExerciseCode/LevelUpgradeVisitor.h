#pragma once

#include "Visitor.h"

class Modifiable;
class Player;
class Shotgun;
class MagicWand;

class LevelUpgradeVisitor : public Visitor
{
public:
	LevelUpgradeVisitor(void);
	~LevelUpgradeVisitor(void);

	inline int getLevel() {return m_level;}
	inline void setLevel(int level) {m_level = level;}

	void visit(Modifiable* visitable);

private:
	void upgrade(Player& p);
	void upgrade(Shotgun& s);
	void upgrade(MagicWand& w);

private:
	int m_level;
};

