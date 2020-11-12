#pragma once
#include <iostream>
#include "Units.h"

namespace Gamma {

	class Item {
		const char name;
		int weight, use_points;
		int x, y;
	protected:
		virtual int Item_id() = 0;
		virtual bool use() = 0;
	public:
		void set_x_y(int,int);
		
	};

	class weapon : public Item {
	private:
		int ammo_type, damage, full_ammo, cur_ammo, RP;
	protected:
		virtual int Item_id() { return 0; };
		virtual bool use(Unit&);
	public:
		
	};

	class aidkit : public Item {
	private:

		int heal_amount, cur_charges, full_charges;
	protected:
		virtual int Item_id() { return 1; };
		virtual bool use(Unit&);
	public:

	};

	class ammunition : public Item {
	private:
		int ammo_type, cur_count, full_count;
	protected:
		virtual int Item_id() { return 2; };
		virtual bool use(Operative&);
	public:

	};
}
