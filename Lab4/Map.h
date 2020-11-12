#pragma once
#include <iostream>
#include "Units.h"

namespace Gamma {

	class GameField {
	private:
		int h, l;
		Unit* player[3];
		Unit* enemy[3];
		Item** items;
	public:
	};
}
