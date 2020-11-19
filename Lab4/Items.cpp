#include "classes.h"

using namespace Gamma;

inline double Gamma::weapon::deal_damage()
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

int Gamma::Item::UP() const
{
	return use_points;
}
