#include "classes.h"

using namespace Gamma;
GameField::GameField() : h(19), l(80)
{
	for (int i = 0; i < 3; i++)
		player.push_back(new Operative());

	enemy.push_back(new Alien_friendly());
	enemy.push_back(new Alien_melee());
	enemy.push_back(new Alien_range());

	Map.resize(l);
	for (int i = 0; i < l; i++) {
		Map[i].resize(h);
		for (int j = 0; j < h; j++)
			Map[i][j].type = '.';
	}
}

bool Cell::add_item(Item* item)
{
	if (type == '.') {
		Items.push_back(item);
		return true;
	}
	return false;
}
