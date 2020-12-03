#pragma once
#include "classes.h"
#include "Units.h"

namespace Gamma {

	class Item {
	protected:
		std::string name;
		int weight, use_points;
	public:
		Item() : name("noname"), weight(), use_points() {}
		Item(std::string, int, int);
		~Item() {}

		inline int up() const { return use_points; }
		inline int w() const { return weight; }

		virtual bool use(Operative*) = 0;
	};


	class weapon : public Item {
	private:
		int cur_clip_ammo,
			full_clip_ammo,
			damage, reload_points;
		double ammo_type;
	public:
		weapon() : Item(), cur_clip_ammo(), full_clip_ammo(), damage(), reload_points(), ammo_type() {}
		weapon(std::string n, int w, int up, int f_clip_ammo, int f_ammo, int d, int rp, double a_type);
		~weapon() {}

		double deal_damage();
		int reload(int, double);
		virtual bool use(Operative*);
	};


	class aidkit : public Item {
	private:
		int heal_amount, charges, full_charges;
	public:
		aidkit() : Item(), heal_amount(), charges(), full_charges() {}
		aidkit(std::string n, int w, int up, int heal, int chrgs);
		~aidkit() {}

		virtual bool use(Operative*);
	};


	class ammunition : public Item {
	private:
		int cur_count, full_count;
		double ammo_type;
	public:
		ammunition() : Item(), cur_count(), full_count(), ammo_type() {}
		ammunition(std::string n, int w, int up, int count, double a_type);
		~ammunition() {}

		virtual bool use(Operative*);
	};
}
