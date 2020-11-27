#pragma once
#include "classes.h"

namespace Gamma {

	class Backpack {
	private:
		int weight, num;
		std::map<char, Item*> Items;
	public:
		Backpack(std::vector<char> binds = { 'q','w','e','r' });
		~Backpack() {}

		bool put_item(Item*);
		Item* drop_item(char);
		void delete_item(char);
		inline Item* choose_item(char bind) const;
	};


	class Unit {
	private:
		std::string name;
		int cur_HP, cur_MP;
		const int full_HP, full_MP,
			vision,
			move_points;
		int x, y;
	public:
		Unit() : name("noname"), x(), y(), cur_HP(), full_HP(), cur_MP(), full_MP(), vision(), move_points() {}
		Unit(std::string n, int x_ = -1, int y_ = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Unit() {}

		int change_HP(int);
		inline void change_MP(int);
		inline bool check_MP(int) const;
		inline bool is_alive() const;
	};


	class Operative : public Unit {
	private:
		const double accuracy;
		const int full_weight;
		Backpack backpack;
		weapon* gun;
	public:
		Operative() : Unit(), backpack(), gun(nullptr), accuracy(), full_weight() {}
		Operative(std::vector<char> binds, weapon* g, double ac, int f_w, 
			std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Operative() { delete gun; }

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
		Alien_melee() : Unit(), accuracy(), damage(), attack_points() {}
		Alien_melee(double ac, int d, int ap, 
			std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Alien_melee() {}

		bool attack(Unit*);
	};


	class Alien_range : public Unit {
	private:
		double accuracy;
		weapon* gun;
	public:
		Alien_range() : Unit(), accuracy(), gun(nullptr) {}
		Alien_range(weapon* g, double ac, std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Alien_range() { delete gun; }

		bool attack(Unit*);
	};


	class Alien_friendly : public Unit {
	private:
		Backpack backpack;
	public:
		Alien_friendly() : Unit(), backpack() {}
		Alien_friendly(std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Alien_friendly() {}

	};
}
