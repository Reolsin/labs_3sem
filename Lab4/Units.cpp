#include "classes.h"

using namespace Gamma;


Backpack::Backpack(std::vector<char> binds) : weight(0), num(0)
{
	for (int i = 0; i < binds.size(); i++)
		Items[binds[i]] = nullptr;
}

bool Backpack::put_item(Item* item)
{
	if (num < Items.size()) {
		for (std::map<char, Item*>::iterator i = Items.begin(); i != Items.end(); i++)
			if (i->second == nullptr) {
				i->second = item;
				weight += item->w();
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
	if (item != nullptr) {
		num--;
		weight -= item->w();
		Items[bind] = nullptr;
	}
	return item;
}

void Backpack::delete_item(char bind)
{
	num--;
	weight -= Items[bind]->w();
	delete Items[bind];
	Items[bind] = nullptr;
}

inline Item* Backpack::choose_item(char bind) const
{
	return Items.at(bind);
}


Operative::Operative(std::vector<char> binds, weapon* g, double ac, int f_w, std::string n, int x, int y, int hp, int mp, int r, int move) :
	Unit(n, x, y, hp, mp, r, move), backpack(binds), gun(g), accuracy(ac), full_weight(f_w) {}

bool Operative::attack(Unit* unit)
{
	if (check_MP(gun->up())) {
		int n;
		if (n = gun->deal_damage()) {
			change_MP(gun->up());
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


Unit::Unit(std::string n, int x_, int y_, int hp, int mp, int r, int move) :
	name(n), x(x_), y(y_), cur_HP(hp), full_HP(hp), cur_MP(mp), full_MP(mp), vision(r), move_points(move) {}

int Unit::change_HP(int HP)
{
	int n = (HP > full_HP - cur_HP) ? full_HP - cur_HP : HP;
	cur_HP += n;
	return n;
}

inline void Unit::change_MP(int use_points) 
{ 
	cur_MP -= use_points; 
}

inline bool Unit::check_MP(int MP) const 
{ 
	return cur_MP >= MP; 
}

inline bool Unit::is_alive() const 
{ 
	return cur_HP > 0; 
}


Alien_melee::Alien_melee(double ac, int d, int ap, std::string n, int x, int y, int hp, int mp, int r, int move) :
	Unit(n, x, y, hp, mp, r, move), accuracy(ac), damage(d), attack_points(ap) {}

bool Alien_melee::attack(Unit* unit)
{
	if (check_MP(attack_points)) {
		change_MP(attack_points);
		unit->change_HP(-(accuracy * damage));
		return true;
	}
	return false;
}


Alien_range::Alien_range(weapon* g, double ac, std::string n, int x, int y, int hp, int mp, int r, int move) :
	Unit(n, x, y, hp, mp, r, move),  gun(g), accuracy(ac) {}

bool Alien_range::attack(Unit* unit)
{
	if (check_MP(gun->up())) {
		int n;
		if (n = gun->deal_damage()) {
			change_MP(gun->up());
			unit->change_HP(-(accuracy * n));
			return true;
		}
	}
	return false;
}


Alien_friendly::Alien_friendly(std::string n, int x, int y, int hp, int mp, int r, int move) :
	Unit(n, x, y, hp, mp, r, move), backpack() {}
