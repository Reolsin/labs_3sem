#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "conio.h"
#include "windows.h"

namespace Gamma {

	class GameSession;
	class GameLevel;
	struct Cell;
	struct Point;

	class Unit;
	class Operative;
	class Alien_melee;
	class Alien_range;
	class Alien_friendly;

	class Item;
	class aidkit;
	class ammunition;
	class weapon;

	const std::string msgs[] = {
		"Success.", "Need to reload weapon.", "Unit doesnt have enough action points.", "Unit has full HP.", "Aidkit hasnt charges.",
		"Weapon has full clip or wrong ammo type.", "No ammo in container.", "Choosed empty slot.", "Unit cant move here.", "Unit is dead.",
		"Inventory mode activated.", "Unit dont have Backpack", "Choose item to take.", "No items on this cell.", "Unit cant take this item.", 
		"No dead units on this cell.", "Choose target.", "Unit dont have weapon." };

	const std::string close_mods[] = { "Game loaded.", "Inventory mode closed.", "Attack mode closed.", "Take mode closed.", "Loot mode closed." };
}
