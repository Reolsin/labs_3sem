#include "classes.h"

using namespace Gamma;

Backpack::Backpack() : weight(0), num(0)
{
	Items['q'] = nullptr;
	Items['w'] = nullptr;
	Items['e'] = nullptr;
	Items['r'] = nullptr;
}

bool Backpack::put_item(Item* item)
{
	if (num < Items.size()) {
		for (std::map<char, Item*>::iterator i = Items.begin(); i != Items.end(); i++)
			if (i->second == nullptr) {
				i->second = item;
				num++;
				break;
			}
		return true;
	}
	return false;
}

Item* Backpack::drop_item(char bind)
{
	Item* item = Items[bind];
	if (item)
		num--;
	Items[bind] = nullptr;
	return item;
}

void Backpack::delete_item(char bind)
{
	delete Items[bind];
	num--;
	Items[bind] = nullptr;
}

inline Item* Backpack::choose_item(char bind)
{
	return Items[bind];
}

bool Operative::attack(Unit* unit)
{ 
	if (check_MP(gun->UP())) {
		int n;
		if (n = gun->deal_damage()) {
			change_MP(gun->UP());
			unit->change_HP(-(accuracy * n));
			return true;
		}
	}
	return false;
}

bool Operative::use_item(char bind)
{
	Item* item = backpack.choose_item(bind);
	if (item) {
		return item->use(this);
	}
	return false;
}

int Operative::change_ammo(int cur_ammo, double ammo_type)
{
	return gun->change_ammo(cur_ammo, ammo_type);
}

bool Operative::change_weapon(weapon* gun2)
{
	std::swap(*gun, *gun2);
	return true;
}

Unit::Unit() : name('A'), cur_HP(100), full_HP(100), cur_MP(100), full_MP(100), vision_Rad(10), move_points(), x(0), y(0) {}

int Unit::change_HP(int HP)
{
	int n = (HP > full_HP - cur_HP) ? full_HP - cur_HP : HP;
	cur_HP += n;
	return n;
}

inline void Unit::change_MP(int use_points) { cur_MP -= use_points; }

inline bool Unit::check_MP(int MP) const { return cur_MP >= MP; }

inline bool Unit::is_Alive() const { return cur_HP > 0; }

bool Alien_range::attack(Unit* unit)
{
	if (check_MP(gun->UP())) {
		int n;
		if (n = gun->deal_damage()) {
			change_MP(gun->UP());
			unit->change_HP(-(accuracy * n));
			return true;
		}
	}
	return false;
}

bool Alien_melee::attack(Unit* unit)
{
	if (check_MP(attack_points)) {
		change_MP(attack_points);
		unit->change_HP(-(accuracy * damage));
		return true;
	}
	return false;
}
