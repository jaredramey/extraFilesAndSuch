#include "StdAfx.h"
#include "Shotgun.h"
#include "Visitor.h"
#include <iostream>

Shotgun::Shotgun(void)
{
	m_bIsDualShotgunEnabled = false;
}

Shotgun::~Shotgun(void)
{
}

Shotgun::Shotgun(const Shotgun& s) {
	m_bIsDualShotgunEnabled = s.m_bIsDualShotgunEnabled;	
}

Shotgun& Shotgun::operator=(const Shotgun& s) {
	m_bIsDualShotgunEnabled = s.m_bIsDualShotgunEnabled;
	return *this;
}

void Shotgun::primaryAttack() 
{
	std::cout << "Shotgun: single shot" << std::endl;	
}

void Shotgun::secondaryAttack() 
{
	if(m_bIsDualShotgunEnabled) {
		std::cout << "Shotgun: dual shot" << std::endl;
	}
}

void Shotgun::letsModify(Visitor* visitor)
{
	visitor->visit(this);
}