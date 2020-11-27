#include "classes.h"

using namespace Gamma;


Item::Item(std::string n, int w, int up) :
	name(n), weight(w), use_points(up) {}

inline int Item::up() const { return use_points; }

inline int Item::w() const { return weight; }


weapon::weapon(std::string n, int w, int up, int f_clip_ammo, int f_ammo, int d, int rp, double a_type) :
	Item(n, w, up), cur_clip_ammo(f_clip_ammo), full_clip_ammo(f_clip_ammo), cur_ammo(f_ammo), full_ammo(f_ammo), damage(d), reload_points(rp), ammo_type(a_type) {}

inline double weapon::deal_damage()
{
	if (cur_clip_ammo) {
		cur_ammo--;
		cur_clip_ammo--;
		return damage * ammo_type;
	}
	return 0;
}

int weapon::change_ammo(int ammo, double type)
{
	int n = 0;
	if (ammo_type == type) {
		n = (ammo > full_ammo - cur_ammo) ? full_ammo - cur_ammo : ammo;
		cur_ammo += n;
	}
	return n;
}

bool weapon::use(Operative* unit)
{
	return unit->change_weapon(this);
}


aidkit::aidkit(std::string n, int w, int up, int heal, int chrgs) :
	Item(n, w, up), heal_amount(heal), charges(chrgs) {}

bool aidkit::use(Operative* unit)
{
	if (charges) {
		if (unit->check_MP(use_points))
			if (unit->change_HP(heal_amount)) {
				unit->change_MP(use_points);
				charges--;
				return true;
			}
	}
	return false;
}


ammunition::ammunition(std::string n, int w, int up, int count, double a_type) :
	Item(n, w, up), cur_count(count), full_count(count), ammo_type(a_type) {}

bool ammunition::use(Operative* unit)
{
	if (cur_count) {
		int n;
		if (unit->check_MP(use_points))
			if (n = unit->change_ammo(cur_count, ammo_type)) {
				unit->change_MP(use_points);
				cur_count -= n;
				return true;
			}
	}
	return false;
}
