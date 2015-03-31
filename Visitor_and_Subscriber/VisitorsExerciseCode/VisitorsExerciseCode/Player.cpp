#include "StdAfx.h"
#include "Player.h"
#include "Visitor.h"
#include "Weapon.h"

Player::Player(void)
{
	m_points = 1;
}


Player::~Player(void)
{
	m_weaponList.clear();
}

Player::Player(const Player& p) {
	m_points = p.m_points;
	m_weaponList = p.m_weaponList;
}

Player& Player::operator= (const Player& p) {
	m_points = p.m_points;
	m_weaponList = p.m_weaponList;
	return *this;
}

bool Player::addWeapon(Weapon* w) 
{
	m_weaponList.push_back(w);
	return true;
}

void Player::letsModify(Visitor* visitor)
{
	// pass this object to the visitor so that the visitor can modify us
	visitor->visit(this);

	// and then call the letsModify function for each weapon we have
	for each(Weapon* w in m_weaponList) {
		w->letsModify(visitor);
	}
}