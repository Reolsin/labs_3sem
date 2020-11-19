#pragma once
#include "classes.h"

namespace Gamma {

	class Backpack {
	private:
		int weight, num;
		std::map<char, Item*> Items;
	public:
		Backpack();
		Backpack(int, const char*, int);

		bool put_item(Item*);
		Item* drop_item(char);
		void delete_item(char);
		inline Item* choose_item(char bind);
	};


	class Unit {
	private:
		const char name;
		int cur_HP, cur_MP;
		const int full_HP, full_MP,
			vision_Rad,
			move_points;
		int x, y;
	public:
		Unit();
		int change_HP(int);
		inline void change_MP(int);
		inline bool check_MP(int) const;
		inline bool is_Alive() const;
	};


	class Operative : public Unit {
	private:
		const double accuracy;
		const int full_weight;
		Backpack backpack;
		weapon* gun;
	public:
		bool attack(Unit*);

		bool use_item(char bind);
		int change_ammo(int, double);
		bool change_weapon(weapon*);
	};


	class Alien_melee : public Unit {
	private:
		double accuracy;
		int damage;
		int attack_points;
	public:
		bool attack(Unit*);
	};


	class Alien_range : public Unit {
	private:
		double accuracy;
		weapon* gun;
	public:
		bool attack(Unit*);
	};


	class Alien_friendly : public Unit {
	private:
		Backpack backpack;
	public:
	};
}
