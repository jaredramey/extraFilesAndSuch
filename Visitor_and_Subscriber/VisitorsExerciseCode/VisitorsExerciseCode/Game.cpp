#include "StdAfx.h"
#include "Game.h"
#include "Visitor.h"

Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::letsModify(Visitor* visitor) {
	visitor->visit(this);
	m_player1.letsModify(visitor);
}