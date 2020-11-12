#pragma once
#include <iostream>

namespace Gamma {
  
  class GameField {
	private:
		char** Map;
		int h, l;
		Unit* player[3];
		Unit* bots[3];
		Item** items;
	public:
	};
  
  class Item {

	};

	class weapon {
	private:
		const char name;
		int Weight, UP;
		int ammo_type, damage, full_ammo, cur_ammo, RP;
	public:
		
	};

	class aidkit {
	private:
		const char name;
		int Weight, UP;
		int heal, cur_charges, full_charges;
	public:
		
	};

	class ammunition {
	private:
		const char name;
		int Weight, UP;
		int ammo_type, cur_count, full_count;
	public:
		
	};

	class Backpack {

	};

	class Unit {

	};

	class Operative {
	private:
		const char name;
		int cur_HP, cur_MP,
			full_HP, full_MP,
			Vision_Rad,
			Move_P;
		int Accuracy;
		Item* Items[5];
		int weight, full_weight,
			num_items, bp_size;
		weapon* gun;
	public:
		bool take_damage(int);
		int deal_damage();

		bool put_item(Item);
		bool drop_item(int);
		Item& choose_item(int);
		bool use(aidkit&);
		bool use(ammunition&);
		bool change_weapon();
		bool reload();
	};

	class Alien_meelee {
	private:
		const char name;
		int cur_HP, cur_MP,
			full_HP, full_MP,
			Vision_Rad,
			Move_P;
		int Accuracy, damage;
	public:
		int deal_damage();
	};

	class Alien_range {
	private:
		const char name;
		int cur_HP, cur_MP,
			full_HP, full_MP,
			Vision_Rad,
			Move_P;
		int Accuracy;
		weapon* gun;
	public:
		int deal_damage();
	};

	class Alien_friendly {
	private:
		const char name;
		int cur_HP, cur_MP,
			full_HP, full_MP,
			Vision_Rad,
			Move_P;
	public:
	};
}
