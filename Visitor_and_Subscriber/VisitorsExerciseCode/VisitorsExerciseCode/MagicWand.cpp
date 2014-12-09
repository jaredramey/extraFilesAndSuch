#include "StdAfx.h"
#include "MagicWand.h"
#include <iostream>
#include "Visitor.h"

MagicWand::MagicWand(void)
{
	m_powerLevel = 1;
}

MagicWand::~MagicWand(void)
{
}

MagicWand::MagicWand(const MagicWand& w) {
	m_powerLevel = w.m_powerLevel;
}

MagicWand& MagicWand::operator=(const MagicWand& w) {
	m_powerLevel = w.m_powerLevel;
	return *this;
}

void MagicWand::primaryAttack() 
{
	std::cout << "Magic Wand (Power level : " << m_powerLevel << " ) : Primary Attack" << std::endl;	
}

void MagicWand::secondaryAttack()
{
	std::cout << "Magic Wand (Power level : " << m_powerLevel << " ) : Secondary Attack" << std::endl;	
}

void MagicWand::letsModify(Visitor* visitor)
{
	visitor->visit(this);
}