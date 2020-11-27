#pragma once
#include "classes.h"

namespace Gamma {

	struct Cell {
		std::vector<Item*> Items;
		char type;
		bool add_item(Item*);
	};


	class GameField {
	private:
		const int h, l;
		std::vector<Unit*> player;
		std::vector<Unit*> enemy;
		std::vector<std::vector<Cell>> Map;
	public:
		GameField();
		GameField(std::ifstream);
		~GameField() {}
	};
}
