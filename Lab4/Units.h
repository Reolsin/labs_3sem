#pragma once
#include <iostream>
#include "Items.h"

namespace Gamma {

	class Backpack {

	};


	class Unit {
	private:
		const char name;
		int cur_HP, cur_MP,
			full_HP, full_MP,
			vision_Rad,
			move_P;
	public:
		void change_HP(int);
		void change_MP(int);
		bool is_Alive();
	};


	class Operative : public Unit {
	private:
		Item* Items[5];
		int weight, full_weight,
			num_items, backpack_size;
		int number_ammo;
		double accuracy;
		weapon* gun;
	public:
		int deal_damage();

		bool put_item(Item*);
		bool drop_item(int);
		Item* choose_item(int);
		int activate(aidkit*);
		int activate(ammunition*);

		bool change(weapon*);
		bool reload();
	};

	class Alien_meelee : public Unit {
	private:
		double accuracy;
		int damage;
	public:
		int deal_damage();
	};

	class Alien_range : public Unit {
	private:
		double accuracy;
		weapon* gun;
	public:
		int deal_damage();
	};

	class Alien_friendly : public Unit {
	private:
	public:
	};
}
