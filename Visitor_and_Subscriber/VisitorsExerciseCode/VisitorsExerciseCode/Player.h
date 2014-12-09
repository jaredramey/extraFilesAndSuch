#pragma once

#include <vector>
#include "Modifiable.h"

class Weapon;

class Player : public Modifiable
{
public:
	Player(void);
	Player(const Player& p);
	~Player(void);

	Player& operator= (const Player& p);

	inline std::vector<Weapon*>& getWeaponList() {return m_weaponList;}

	bool addWeapon(Weapon* w);

	inline int getPoints() {return m_points;}
	inline void setPoints(int points) {m_points = points;}

	void letsModify(Visitor* visitor);

private:
	std::vector<Weapon*> m_weaponList;
	int m_points;
};

