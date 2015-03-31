// Visitors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Shotgun.h"
#include "MagicWand.h"
#include "LevelUpgradeVisitor.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	Game game;
	LevelUpgradeVisitor luv;

	Player player;
	Shotgun* shotgun = new Shotgun();
	MagicWand* wand = new MagicWand();

	// Initialize the player's values
	player.setPoints(10);
	player.addWeapon(shotgun);
	player.addWeapon(wand);

	// Initialize the game
	game.setPlayer(player);
	game.setLevel(1);

	std::cout << "Before Level Upgrade " << std::endl;
	std::cout << "Initial Level " << game.getLevel() << std::endl;
	std::cout << "Initial Player Points " << game.getPlayer().getPoints() << std::endl ;

	for each(Weapon* w in game.getPlayer().getWeaponList()) {
		w->primaryAttack();
		w->secondaryAttack();
	}
	std::cout << std::endl;

	// Upgrade level
	game.setLevel(2);
	luv.setLevel(game.getLevel());
	game.letsModify(&luv);

	std::cout << std::endl;
	std::cout << "After Level Upgrade " << std::endl;
	std::cout << "New Level " << game.getLevel() << std::endl;
	std::cout << "New Player Points " << game.getPlayer().getPoints() << std::endl;

	for each(Weapon* w in game.getPlayer().getWeaponList()) {
		w->primaryAttack();
		w->secondaryAttack();
	}
	std::cout << std::endl;

	delete shotgun;
	delete wand;

	system("pause");

	return 0;
}

