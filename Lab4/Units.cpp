#include "Units.h"
#include "Items.h"
#include "Session.h"

using namespace Gamma;

Backpack::Backpack(int size) : weight(0), num(0), Items(size, nullptr) {}

Backpack& Backpack::operator=(Backpack&& bp) noexcept
{
	weight = bp.weight;
	num = bp.num;
	std::swap(Items, bp.Items);
	return *this;
}

Backpack::Backpack(std::ifstream& file)
{
	std::string tmp;
	file >> tmp;
	if (tmp == "-")
		*this = Backpack();
	else {
		int n = std::stoi(tmp);
		std::string item_type;
		*this = Backpack(n);
		for (int i = 0; i < n; i++) {
			file >> item_type;
			if (item_type == "weapon")
				put_item(new weapon(file));
			else if (item_type == "aidkit")
				put_item(new aidkit(file));
			else if (item_type == "ammunition")
				put_item(new ammunition(file));
		}
	}
}

std::ofstream& Backpack::save(std::ofstream& ofile) const
{
	if (num == 0)
		ofile << '-';
	else {
		ofile << Items.size();
		for (size_t i = 0; i < Items.size(); i++)
			if (Items[i]) {
				ofile << ' '; ofile << *(Items[i]);
			}
			else
				ofile << " -";
	}
	return ofile;
}

Backpack::~Backpack()
{
	for (int i = 0; i < Items.size(); i++)
		delete Items[i];
}

bool Backpack::put_item(Item* item)
{
	if (num < (int)Items.size()) {
		for (std::vector<Item*>::iterator i = Items.begin(); i != Items.end(); i++)
			if (*i == nullptr) {
				*i = item;
				weight += item->w(); num++;
				break;
			}
		return true;
	}
	return false;
}

Item* Backpack::drop_item(int n)
{
	Item* item = Items[n];
	if (item != nullptr) {
		num--;
		weight -= item->w();
		Items[n] = nullptr;
	}
	return item;
}

inline Item* Backpack::operator[](int n) const
{
	return Items.at(n);
}


Unit::Unit(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move) :
	name(n), model('0'), position(x, y), cur_HP(cur_hp), full_HP(hp), cur_MP(cur_mp), full_MP(mp), vision_(r), move_points(move) {}

Unit::Unit(std::ifstream& file) { file >> name >> model >> position.x >> position.y >> cur_HP >> full_HP >> cur_MP >> full_MP >> vision_ >> move_points; }

std::ofstream& Unit::save(std::ofstream& ofile) const
{ 
	ofile << name << ' ' << model << ' ' << position.x << ' ' << position.y 
		<< ' ' << cur_HP << ' ' << full_HP << ' ' << cur_MP << ' ' << full_MP << ' ' << vision_ << ' ' << move_points << ' ';
	return ofile; 
}

std::ostream& Unit::display(std::ostream& os) const
{
	return os << "HP: " << cur_HP << '/' << full_HP << ", MP: " << cur_MP << '/' << full_MP << ", Points per 1 move: " << move_points << '\n';
}

bool Unit::move(const Point& p)
{
	if (cur_MP >= move_points) 
	{
		cur_MP -= move_points;
		position = p;
		return true;
	}
	return false;
}

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

bool Unit::is_alive() const 
{ 
	return cur_HP > 0; 
}


Operative::Operative(const Unit& unit, weapon* g, double ac, int f_w, Backpack&& bp) :
	Unit(unit), gun(g), accuracy(ac), full_weight(f_w) { backpack = std::move(bp); }

Operative::Operative(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, weapon* g, double ac, int f_w, Backpack&& bp) :
	Unit(n, x, y, cur_hp, hp, cur_mp, mp, r, move), gun(g), accuracy(ac), full_weight(f_w) { backpack = std::move(bp); }

Operative::Operative(std::ifstream& file) : Unit(file) 
{ 
	std::string tmp;
	file >> accuracy >> full_weight >> tmp;
	if (tmp != "-")
		gun = std::make_unique<weapon>(file);
	backpack = Backpack(file);
}

std::ofstream& Operative::save(std::ofstream& ofile) const
{
	ofile << "ally Operative ";
	Unit::save(ofile);
	ofile << accuracy << ' ' << full_weight;
	if (gun) {
		ofile << ' '; ofile << *gun << ' ';
	}
	else
		ofile << " - ";
	ofile << backpack << '\n';
	return ofile;
}

std::ostream& Operative::display(std::ostream& os) const
{
	os << "Operative, ";
	Unit::display(os);
	return os << "Weight: " << backpack.w() << '/' << full_weight << '\n' << "In hands: " << *gun << ", accuracy - " << accuracy << '\n';
}

bool Operative::attack(Unit* unit)
{
	if (check_MP(gun->up())) {
		double n;
		if (n = gun->deal_damage()) {
			change_MP(gun->up());
			unit->change_HP((int)-(accuracy * n));
			return true;
		}
	}
	return false;
}

bool Operative::attack(Cell& cell)
{
	if (check_MP(gun->up())) {
		if (gun->deal_damage()) {
			change_MP(gun->up());
			cell.cell_type = '.';
			return true;
		}
	}
	return false;
}

std::vector<Item*>* Operative::get_items()
{
	return backpack.get_items();
}

Item* Operative::drop_item(int bind)
{
	return backpack.drop_item(bind);
}

bool Operative::take_item(Item* item)
{
	if ((full_weight >= (backpack.w() + item->w())) && (backpack.not_full()))
		return backpack.put_item(item);
	return false;
}

bool Operative::use_item(int bind)
{
	Item* item = backpack[bind];
	if (item) {
		return item->use(this);
	}
	return false;
}

int Operative::load_ammo(int cur_ammo, double ammo_type)
{
	return gun->reload(cur_ammo, ammo_type);
}

bool Operative::change_weapon(weapon* gun2)
{
	std::swap(*gun, *gun2);
	return true;
}


Alien_melee::Alien_melee(const Unit& unit, int d, int ap, double ac) :
	Unit(unit), accuracy(ac), damage(d), attack_points(ap) {}

Alien_melee::Alien_melee(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, int d, int ap, double ac) :
	Unit(n, x, y, cur_hp, hp, cur_mp, mp, r, move), damage(d), attack_points(ap), accuracy(ac) {}

Alien_melee::Alien_melee(std::ifstream& file) : Unit(file) { file >> accuracy >> damage >> attack_points; }

std::ofstream& Alien_melee::save(std::ofstream& ofile) const
{
	ofile << "enemy Alien_melee ";
	Unit::save(ofile);
	ofile << accuracy << ' ' << damage << ' ' << attack_points << '\n';
	return ofile;
}

std::ostream& Alien_melee::display(std::ostream& os) const
{
	os << "Alien_melee, ";
	Unit::display(os);
	return os << "weapon parameters: damage - " << damage << ", accuracy - " << accuracy << ", points for attack: " << attack_points << "\n\n";
}

bool Alien_melee::attack(Unit* unit)
{
	if (check_MP(attack_points)) {
		change_MP(attack_points);
		unit->change_HP((int)-(accuracy * damage));
		return true;
	}
	return false;
}

bool Alien_melee::attack(Cell& cell)
{
	if (check_MP(attack_points)) {
		change_MP(attack_points);
		cell.cell_type = '.';
		return true;
	}
	return false;
}


Alien_range::Alien_range(const Unit& unit, weapon* g, double ac) :
	Unit(unit),  gun(g), accuracy(ac) {}

Alien_range::Alien_range(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, weapon* g, double ac) :
	Unit(n, x, y, cur_hp, hp, cur_mp, mp, r, move), gun(g), accuracy(ac) {}

Alien_range::Alien_range(std::ifstream& file) : Unit(file) 
{ 
	std::string tmp;
	file >> accuracy >> tmp; 
	if (tmp != "-")
		gun = std::make_unique<weapon>(file);
}

std::ofstream& Alien_range::save(std::ofstream& ofile) const
{
	ofile << "enemy Alien_range ";
	Unit::save(ofile);
	ofile << accuracy;
	if (gun) {
		ofile << ' '; ofile << *gun;
	}
	else
		ofile << " -";
	ofile << '\n';
	return ofile;
}

std::ostream& Alien_range::display(std::ostream& os) const
{
	os << "Alien_range, ";
	Unit::display(os);
	return os << "in hands: " << *gun << "In hands: " << *gun << ", accuracy - " << accuracy << "\n\n";
}

bool Alien_range::attack(Unit* unit)
{
	if (check_MP(gun->up())) {
		double n;
		if (n = gun->deal_damage()) {
			change_MP(gun->up());
			unit->change_HP((int)-(accuracy * n));
			return true;
		}
	}
	return false;
}

bool Alien_range::attack(Cell& cell)
{
	if (check_MP(gun->up())) {
		if (gun->deal_damage()) {
			change_MP(gun->up());
			cell.cell_type = '.';
			return true;
		}
	}
	return false;
}


Alien_friendly::Alien_friendly(const Unit& unit, int f_w, Backpack&& bp) :
	Unit(unit), full_weight(f_w) { backpack = std::move(bp); }

Alien_friendly::Alien_friendly(std::string n, int x, int y, int cur_hp, int hp, int cur_mp, int mp, int r, int move, int f_w, Backpack&& bp) :
	Unit(n, x, y, cur_hp, hp, cur_mp, mp, r, move), full_weight(f_w) { backpack = std::move(bp); }

Alien_friendly::Alien_friendly(std::ifstream& file) : Unit(file)
{
	file >> full_weight;
	backpack = Backpack(file);
}

std::ofstream& Alien_friendly::save(std::ofstream& ofile) const
{
	ofile << "enemy Alien_friendly ";
	Unit::save(ofile);
	ofile << full_weight << ' ';
	ofile << backpack << '\n';
	return ofile;
}

std::ostream& Alien_friendly::display(std::ostream& os) const
{
	os << "Alien_friendly, ";
	Unit::display(os);
	return os << "Weight: " << backpack.w() << '/' << full_weight << "\n\n";
}

std::vector<Item*>* Alien_friendly::get_items()
{
	return backpack.get_items();
}
