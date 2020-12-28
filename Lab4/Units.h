#pragma once
#include "classes.h"

namespace Gamma {

	struct Point {
		int x, y;
		Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

		Point& operator+=(const Point& p) { x += p.x; y += p.y; return *this; }
		bool operator==(const Point& p) const { return (x == p.x) && (y == p.y); }
	};

	class Backpack {
	private:
		int weight;
		int num;
		std::vector<Item*> Items;
	protected:
		std::ofstream& save(std::ofstream&) const;
	public:
		Backpack(int size = 4);
		Backpack(std::ifstream&);
		~Backpack();
		Backpack& operator=(Backpack&&) noexcept;

		inline std::vector<Item*>* get_items() { return &Items; }
		inline int w() const { return weight; }
		inline bool not_full() const { return num < (int)Items.size(); };
		bool put_item(Item*);
		Item* drop_item(int);
		inline Item* operator[](int) const;

		friend std::ofstream& operator<<(std::ofstream& ofile, const Backpack& bp) { return bp.save(ofile); }
	};


	class Unit {
	private:
		std::string name;
		char model;
		int cur_HP, cur_MP;
		int full_HP, full_MP,
			vision_,
			move_points;
		Point position;
	protected:
		Unit() : name("noname"), model('0'), position(), cur_HP(), full_HP(), cur_MP(), full_MP(), vision_(), move_points() {}
		Unit(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move);
		Unit(std::ifstream&);

		virtual bool attack(Unit*) = 0;
		virtual bool attack(Cell&) = 0;
		virtual bool gun_check() const = 0;
		virtual std::ostream& display(std::ostream&) const;
		virtual std::ofstream& save(std::ofstream&) const;
	public:
		bool move(const Point&);
		inline Point pos() const { return position; }
		inline int vision() const { return vision_; }

		inline void refresh() { cur_MP = full_MP; }
		int change_HP(int);
		void change_MP(int);
		bool check_MP(int) const;
		bool is_alive() const;
		inline std::string name_() const { return name; }
		inline char avatar() const { return model; }

		virtual std::vector<Item*>* get_items() = 0;
		friend std::ostream& operator<<(std::ostream& ofile, const Unit& unit) { return unit.display(ofile); }
		friend std::ofstream& operator<<(std::ofstream& ofile, const Unit& unit) { return unit.save(ofile); }
	};


	class Operative : public Unit {
	private:
		double accuracy;
		int full_weight;
		Backpack backpack;
		std::unique_ptr<weapon> gun;
	protected:
		virtual std::ostream& display(std::ostream&) const;
		virtual std::ofstream& save(std::ofstream&) const;
	public:
		Operative() : Unit(), accuracy(), full_weight() {}
		Operative(const Unit&, weapon*, double, int, Backpack&&);
		Operative(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, weapon*, double, int, Backpack&&);
		Operative(std::ifstream&);

		Item* drop_item(int);
		bool take_item(Item*);
		bool use_item(int);
		int load_ammo(int, double);
		bool change_weapon(weapon*);

		virtual bool attack(Unit*);
		virtual bool attack(Cell&);
		virtual std::vector<Item*>* get_items();
		virtual bool gun_check() const { return gun != nullptr; }
	};


	class Alien_melee : public Unit {
	private:
		double accuracy;
		int damage, attack_points;
	protected:
		virtual std::ostream& display(std::ostream&) const;
		virtual std::ofstream& save(std::ofstream&) const;
	public:
		Alien_melee() : Unit(), accuracy(), damage(), attack_points() {}
		Alien_melee(const Unit&, int, int, double);
		Alien_melee(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, int d, int ap, double ac);
		Alien_melee(std::ifstream&);

		virtual bool attack(Unit*);
		virtual bool attack(Cell&);
		virtual std::vector<Item*>* get_items() { return nullptr; }
		virtual bool gun_check() const { return damage != 0; }
	};


	class Alien_range : public Unit {
	private:
		double accuracy;
		std::unique_ptr<weapon> gun;
	protected:
		virtual std::ostream& display(std::ostream&) const;
		virtual std::ofstream& save(std::ofstream&) const;
	public:
		Alien_range() : Unit(), accuracy() {}
		Alien_range(const Unit&, weapon*, double);
		Alien_range(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, weapon*, double ac);
		Alien_range(std::ifstream&);

		virtual bool attack(Unit*);
		virtual bool attack(Cell&);
		virtual std::vector<Item*>* get_items() { return nullptr; }
		virtual bool gun_check() const { return gun != nullptr; }
	};


	class Alien_friendly : public Unit {
	private:
		int full_weight;
		Backpack backpack;
	protected:
		virtual std::ostream& display(std::ostream&) const;
		virtual std::ofstream& save(std::ofstream&) const;
	public:
		Alien_friendly() : Unit(), full_weight(), backpack() {}
		Alien_friendly(const Unit&, int, Backpack&&);
		Alien_friendly(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, int full_weight, Backpack&&);
		Alien_friendly(std::ifstream&);

		virtual bool attack(Unit*) { return false; }
		virtual bool attack(Cell&) { return false; }
		virtual std::vector<Item*>* get_items();
		virtual bool gun_check() const { return false; }
	};
}
