#pragma once
#include "classes.h"

namespace Gamma {

	struct Point {
		int x, y;
		Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
		Point& operator+=(const Point& p) { x += p.x; y += p.y; }
	};

	class Backpack {
	private:
		int weight;
		size_t num;
		std::map<char, Item*> Items;
	public:
		Backpack(std::vector<char> binds = { 'q','w','e','r' });
		~Backpack() {}

		int w() const { return weight; }
		bool put_item(Item*);
		Item* drop_item(char);
		inline Item* operator[](char bind) const;
	};


	class Unit {
	private:
		std::string name;
		int cur_HP, cur_MP;
		const int full_HP, full_MP,
			vision,
			move_points;
		Point position;
	public:
		Unit() : name("noname"), position(), cur_HP(), full_HP(), cur_MP(), full_MP(), vision(), move_points() {}
		Unit(std::string n, int x_ = -1, int y_ = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Unit() {}

		bool move(const Point&);
		Point get_pos() const { return position; }

		int change_HP(int);
		void change_MP(int);
		bool check_MP(int) const;
		bool is_alive() const;

		virtual bool attack(Unit*) = 0;
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

		virtual bool attack(Unit*);

		Item* drop_item(char bind);
		bool take_item(Item*);
		bool use_item(char bind);
		int load_ammo(int, double);
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

		virtual bool attack(Unit*);
	};


	class Alien_range : public Unit {
	private:
		double accuracy;
		weapon* gun;
	public:
		Alien_range() : Unit(), accuracy(), gun(nullptr) {}
		Alien_range(weapon* g, double ac, std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Alien_range() { delete gun; }

		virtual bool attack(Unit*);
	};


	class Alien_friendly : public Unit {
	private:
		Backpack backpack;
	public:
		Alien_friendly() : Unit(), backpack() {}
		Alien_friendly(std::string n, int x = -1, int y = -1, int hp = 100, int mp = 100, int r = 5, int move = 20);
		~Alien_friendly() {}

		virtual bool attack(Unit*) { return false; }
	};
}
