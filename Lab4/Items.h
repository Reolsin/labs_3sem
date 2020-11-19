#pragma once
#include "classes.h"

namespace Gamma {

	class Item {
	protected:
		const char name;
		int weight, use_points;
	public:
		Item();
		Item(char, int, int);
		int UP() const;

		virtual bool use(Operative*) = 0;
	};

	class weapon : public Item {
	private:
		int cur_clip_ammo, cur_ammo, 
			full_clip_ammo, full_ammo, 
			damage, reload_points;
		double ammo_type;
	public:
		weapon();
		weapon(int, int, int, int, double);
		
		double deal_damage();
		int change_ammo(int, double);
		virtual bool use(Operative*);
	};

	class aidkit : public Item {
	private:
		int heal_amount, charges;
	public:
		aidkit();
		aidkit(int, int);

		virtual bool use(Operative*);
	};

	class ammunition : public Item {
	private:
		int cur_count, full_count;
		double ammo_type;
	public:
		ammunition();
		ammunition(int, double);

		virtual bool use(Operative*);
	};
}
