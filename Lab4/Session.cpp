#include "Session.h"
#include <math.h>
#define pi 3.1412

using namespace Gamma;

Cell::~Cell()
{
	for (size_t i = 0; i < Items.size(); i++)
		delete Items[i];
}

bool Cell::add_item(Item* item)
{
	if (cell_type == '.' || cell_type == '?') {
		cell_type = '?';
		Items.push_back(item);
		return true;
	}
	return false;
}


GameLevel::GameLevel(int l_, int h_) : l(l_), h(h_)
{
	Map.resize(h);
	for (int i = 0; i < h; i++) {
		Map[i].resize(l);
		for (int j = 0; j < l; j++)
			Map[i][j].cell_type = '.';
	}
}

GameLevel::GameLevel(std::ifstream& file)
{
	file >> h >> l; file.ignore(1);
	Map.resize(h);
	for (int i = 0; i < h; i++) {
		Map[i].resize(l);
		for (int j = 0; j < l; j++)
			file >> Map[i][j].cell_type;
		file.ignore(1);
	}
	int number_items, x, y;
	std::string item_type;
	file >> number_items; file.ignore(1);
	for (int i = 0; i < number_items; i++) {
		file >> x >> y >> item_type;
		if (item_type == "weapon")
			add_item(new weapon(file), x, y);
		else if (item_type == "aidkit")
			add_item(new aidkit(file), x, y);
		else if (item_type == "ammunition")
			add_item(new ammunition(file), x, y);
		file.ignore(1);
	}
}

std::ofstream& GameLevel::save(std::ofstream& ofile) const
{
	ofile << h << ' ' << l << '\n';
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < l; j++)
			ofile << Map[i][j].cell_type;
		ofile << '\n';
	}
	int n = 0;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < l; j++)
			for (size_t k = 0; k < Map[i][j].Items.size(); k++)
				n++;
	ofile << n << '\n';
	for (int i = 0; i < h; i++)
		for (int j = 0; j < l; j++)
			for (size_t k = 0; k < Map[i][j].Items.size(); k++) {
				ofile << j << ' ' << i << ' '; ofile << *(Map[i][j].Items[k]) << '\n';
			}
	return ofile;
}

Cell& GameLevel::operator[](const Point& p)
{
	return Map[p.y][p.x];
}

std::vector<Item*>* GameLevel::get_items(const Point& p)
{
	return &Map[p.y][p.x].Items;
}

bool GameLevel::add_item(Item* item, int x, int y)
{ 
	if (x >= 0 && x < l)
		if (y >= 0 && y < h)
			return Map[y][x].add_item(item);
	return false;
}

bool GameLevel::point_access(int y, int x) const { return point_on_map(y, x) && (Map[y][x].cell_type == '.' || Map[y][x].cell_type == '?'); }

bool  GameLevel::point_on_map(double y, double x) const { return (l > (int)x) && (0 <= x) && (h > (int)y) && (0 <= y); }

std::vector<std::vector<char>> GameLevel::render_vision(const Unit* unit, const GameSession* Session) const
{
	Point c = unit->pos();
	int nrad = unit->vision();
	int n = nrad * 2 + 1;
	std::vector<std::vector<char>> vision_circle(n, std::vector<char>(n, ' '));
	Unit* other_unit;

	double increment = atan(nrad / (nrad - 1)) - (pi / 4), angle = 0, x0 = c.x + 0.5, y0 = c.y + 0.5;
	do {
		double x, y;
		int distance = 0;
		do {
			distance += 1;
			x = cos(angle) * distance + x0;
			y = sin(angle) * distance + y0;
			if (point_on_map(y, x)) {
				if (other_unit = Session->unit_here(Point((int)x, (int)y)))
					if (other_unit->is_alive())
						vision_circle[(int)y - c.y + nrad][(int)x - c.x + nrad] = other_unit->avatar();
					else
						vision_circle[(int)y - c.y + nrad][(int)x - c.x + nrad] = 'x';
				else
					vision_circle[(int)y - c.y + nrad][(int)x - c.x + nrad] = Map[(int)y][(int)x].cell_type;
			}
		} while ((distance < nrad) && point_on_map(y, x) && is_transparent(y, x));
		angle += increment;
	} while (angle <= 2 * pi);

	if (Session->current_unit_is_alive())
		vision_circle[nrad][nrad] = unit->avatar();
	else
		vision_circle[nrad][nrad] = 'x';

	return vision_circle;
}

bool GameLevel::is_transparent(double y, double x) const
{
	char c = Map[(int)y][(int)x].cell_type;
	return (c == '.') || (c == '-') || (c == '|') || (c == '?') || (c == 'x');
}


GameSession::GameSession(std::ifstream& file) : con_len(160), message(close_mods), current_mode(mode::game), level(file)
{
	int unit_number;
	file >> unit_number; file.ignore(1);
	std::string unit_type, team;

	for (int i = 0; i < unit_number; i++) {
		file >> team >> unit_type;

		if (unit_type == "Operative")
			player.push_back(new Operative(file));
		else if (unit_type == "Alien_friendly")
			enemy.push_back(new Alien_friendly(file));
		else if (unit_type == "Alien_range")
			enemy.push_back(new Alien_range(file));
		else if (unit_type == "Alien_melee")
			enemy.push_back(new Alien_melee(file));

		file.ignore(1);
	}
	file.close();
	current_unit = player[current_unit_num];
	unit_vision = level.render_vision(current_unit, this);
}

bool GameSession::save(std::ofstream& ofile)
{
	ofile << level;
	ofile << player.size() + enemy.size() << '\n';
	for (size_t i = 0; i < player.size(); i++)
		ofile << *(player[i]);
	for (size_t i = 0; i < enemy.size(); i++)
		ofile << *(enemy[i]);
	ofile.close();
	return true;
}

GameSession::~GameSession()
{
	for (size_t i = 0; i < player.size(); i++)
		delete player[i];
	for (size_t i = 0; i < enemy.size(); i++)
		delete enemy[i];
}

Unit* GameSession::unit_here(const Point& p) const
{
	for (size_t i = 0; i < player.size(); i++)
		if (i != current_unit_num)
			if (player[i]->pos() == p)
				return player[i];
	for (size_t i = 0; i < enemy.size(); i++)
		if (enemy[i]->pos() == p)
			return enemy[i];
	return nullptr;
}

void GameSession::move(const Point& next_pos)
{
	Unit* unit = unit_here(next_pos);
	if (current_unit->is_alive())
		if (level.point_access(next_pos.y, next_pos.x) && ((unit) ? !unit->is_alive() : true)) {
			if (current_unit->move(next_pos)) {
				message = msgs;
				unit_vision = level.render_vision(current_unit, this);
			}
			else message = msgs + 2;
		}
		else message = msgs + 8;
	else message = msgs + 9;
}

bool GameSession::move_up()
{
	move(current_unit->pos() += Point(0, 1));
	return true;
}
bool GameSession::move_down()
{
	move(current_unit->pos() += Point(0,-1));
	return true;
}
bool GameSession::move_right() 
{ 
	move(current_unit->pos() += Point(1, 0));
	return true; 
}
bool GameSession::move_left() 
{ 
	move(current_unit->pos() += Point(-1, 0));
	return true; 
}

bool GameSession::choose_next() 
{
	current_unit_num = (current_unit_num + 1) % player.size();
	current_unit = player[current_unit_num];
	unit_vision = level.render_vision(current_unit, this);
	return true;
}

bool GameSession::choose_previous() 
{ 
	current_unit_num = (player.size() + current_unit_num - 1) % player.size();
	current_unit = player[current_unit_num];
	unit_vision = level.render_vision(current_unit, this);
	return true;
}

bool GameSession::inventory_init()
{
	if (current_unit->is_alive()) {
		displayed_items = current_unit->get_items();
		if (displayed_items) {
			displayed_items_num = 0;
			current_mode = mode::inventory;
			message = msgs + 10;
		}
		else message = msgs + 11;
	}
	else message = msgs + 9;
	return true;
}

bool GameSession::inventory_drop()
{
	Item* item = current_unit->drop_item(displayed_items_num);
	if (item) {
		level[current_unit->pos()].add_item(item);
		message = msgs;
	}
	else message = msgs + 7;
	return true;
}

bool GameSession::inventory_activate()
{
	message = current_unit->use_item(displayed_items_num);
	return true;
}

bool GameSession::take_init()
{
	if (current_unit->is_alive()) {
		displayed_items = level.get_items(current_unit->pos());
		if ((displayed_items->size() > 0)) {
			displayed_items_num = 0;
			current_mode = mode::take;
			message = msgs + 12;
		}
		else message = msgs + 13;
	}
	else message = msgs + 9;
	return true;
}

bool GameSession::take_activate()
{
	if (current_unit->take_item(displayed_items->at(displayed_items_num))) {
		std::swap(displayed_items->at(displayed_items_num), displayed_items->back());
		displayed_items->pop_back();
		if (displayed_items->size() == 0)
			level[current_unit->pos()].cell_type = '.';
		message = msgs;
	}
	else message = msgs + 14;
	return true;
}

bool GameSession::loot_init()
{
	if (current_unit->is_alive()) {
		Unit* unit = unit_here(current_unit->pos());
		if (unit) {
			displayed_items = unit->get_items();
			if (displayed_items) {
				displayed_items_num = 0;
				current_mode = mode::take;
				message = msgs + 12;
			}
			else message = msgs + 13;
		}
		else message = msgs + 15;
	}
	else message = msgs + 9;
	return true;
}

bool GameSession::loot_activate()
{
	if (current_unit->take_item(displayed_items->at(displayed_items_num))) {
		displayed_items->at(displayed_items_num) = nullptr;
		message = msgs;
	}
	else message = msgs + 14;
	return true;
}

bool GameSession::table_choose_up()
{
	displayed_items_num = (displayed_items->size() + displayed_items_num - 1) % displayed_items->size();
	return true;
}

bool GameSession::table_choose_down()
{
	displayed_items_num = (displayed_items_num + 1) % displayed_items->size();
	return true;
}

bool GameSession::attack_init()
{
	if (current_unit->is_alive()) {
		if (current_unit->gun_check()) {
			current_mode = mode::attack;
			attack_cursor = current_unit->pos();
			message = msgs + 16;
		}
		else message = msgs + 17;
	}
	else message = msgs + 9;
	return true;
}

void GameSession::attack_cursor_move(const Point& next_position)
{
	size_t y = next_position.y - current_unit->pos().y + current_unit->vision(),
		x = next_position.x - current_unit->pos().x + current_unit->vision();
	if ((0 < y) && (y < unit_vision.size()) && (0 < x) && (x < unit_vision.size()))
		if (unit_vision[y][x] != ' ')
			attack_cursor = next_position;
}

bool GameSession::attack_cursor_up()
{
	attack_cursor_move(Point(0, 1) += attack_cursor);
	return true;
}

bool GameSession::attack_cursor_down()
{
	attack_cursor_move(Point(0, -1) += attack_cursor);
	return true;
}

bool GameSession::attack_cursor_left()
{
	attack_cursor_move(Point(-1, 0) += attack_cursor);
	return true;
}

bool GameSession::attack_cursor_right()
{
	attack_cursor_move(Point(1, 0) += attack_cursor);
	return true;
}

bool GameSession::attack_activate()
{
	Point pos = current_unit->pos();
	Unit* other_unit = nullptr;
	int nrad = current_unit->vision();
	double angle = (attack_cursor.x - pos.x == 0) ? (attack_cursor.y - pos.y > 0 ? pi / 2 : -pi / 2) : atan((double)(attack_cursor.y - pos.y) / (attack_cursor.x - pos.x));
	double x, y, x0 = pos.x + 0.5, y0 = pos.y + 0.5;
	double distance = 0;
	do {
		distance += 0.25;
		x = cos(angle) * distance + x0;
		y = sin(angle) * distance + y0;
		if (level.point_on_map(y, x)) {
			if (other_unit = unit_here(Point((int)x, (int)y))) {
				message = current_unit->attack(other_unit);
				break;
			}
			else if (level[Point((int)x, (int)y)].cell_type != '.') {
				message = current_unit->attack(level[Point((int)x, (int)y)]);
				break;
			}
		}
	} while ((distance < nrad) && level.point_on_map(y, x));
	unit_vision = level.render_vision(current_unit, this);
	current_mode = mode::game;
	return true;
}

bool GameSession::next_turn()
{
	//enemy_turn();
	for (size_t i = 0; i < player.size(); i++)
		player[i]->refresh();
	return true;
}

bool GameSession::close()
{
	message = close_mods + (int)current_mode;
	current_mode = mode::game;
	return true;
}

bool GameSession::exit()
{
	return false;
}

bool GameSession::check() const
{
	bool status = false;
	for (size_t i = 0; i < player.size(); i++)
		status = status || player[i]->is_alive();
	if (status) {
		status = false;
		for (size_t i = 0; i < enemy.size(); i++)
			status = status || enemy[i]->is_alive();
	}
	return status;
}

void GameSession::draw() const
{
	using std::cout; using std::endl;

	system("cls");

	switch (current_mode) {
	case mode::game:
		cout << "binds: menu - escape; attack - 'a'; inventory - 'i'; take - 't'; loot - 'l' ; next turn - 'n';" << endl
			<< "       switch units - pageup/pagedown; moving - up/down/right/left arrows." << endl;
		break;
	case mode::inventory:
		cout << "binds: close - escape, 'i'; drop - 'd'; activate - enter; switch items - up/down arrows." << endl << endl;
		break;
	case mode::take:
		cout << "binds: close - escape, 't'; take - enter; switch items - up/down arrows." << endl << endl;
		break;
	case  mode::attack:
		cout << "binds: close - escape, 'a'; attack - enter; move cursor - up/down/right/left arrows." << endl << endl;
		break;
	case mode::loot:
		cout << "binds: close - escape, 'l'; take - enter; switch items - up/down arrows." << endl << endl;
		break;
	}
	for (int i = 0; i < con_len; i++)
			cout << '-';

	if ((current_mode == mode::game) || (current_mode == mode::attack))
		cout << "Choosed unit: " << current_unit->name_() << ", avatar: " << current_unit->avatar() << endl;
	if ((current_mode == mode::inventory) || (current_mode == mode::loot) || (current_mode == mode::take))
		cout << "Choosed item number: " << displayed_items_num + 1 << endl;

	for (int i = 0; i < con_len; i++)
		cout << '-';

	cout << "Result of last action: " << *message << endl;

	for (int i = 0; i < con_len; i++)
		cout << '-';

	if ((current_mode == mode::attack) || (current_mode == mode::game)) {
		for (size_t i = 0; i < unit_vision.size(); i++) {
			for (size_t j = 0; j < unit_vision[i].size(); j++)
				if ((current_mode == mode::attack) && (i == attack_cursor.y - current_unit->pos().y + current_unit->vision()) && (j == attack_cursor.x - current_unit->pos().x + current_unit->vision()))
					cout << '*';
				else
					cout << unit_vision[i][j];
			cout << endl;
		}
	}
	else if ((current_mode == mode::take) || (current_mode == mode::inventory) || (current_mode == mode::loot)) {
		size_t brdr_end = 2 * current_unit->vision() + 1;
		size_t brdr_start = (displayed_items_num < brdr_end) ? 0 : displayed_items_num - brdr_end + 1;
		brdr_end += brdr_start;
		for (size_t i = brdr_start; i < brdr_end; i++) {
			if (i < displayed_items->size()) {
				if (displayed_items->at(i)) {
					cout << *(displayed_items->at(i));
				}
				else
					cout << "Empty backpack slot";
				if (displayed_items_num == i)
					cout << '<';
			}
			cout << endl;
		}
	}
	for (int i = 0; i < con_len; i++)
		cout << '-';

	cout << "Choosed unit: " << current_unit->avatar() << endl << *current_unit;

	for (int i = 0; i < con_len; i++)
		cout << '-';
}

std::map<operation_code, bool (GameSession::*)(), CompareType> GameSession::operation{
	{{27, mode::game }, &GameSession::exit},
	{{73, mode::game }, &GameSession::choose_next},
	{{81, mode::game }, &GameSession::choose_previous},
	{{80, mode::game }, &GameSession::move_up},
	{{72, mode::game }, &GameSession::move_down},
	{{75, mode::game }, &GameSession::move_left},
	{{77, mode::game }, &GameSession::move_right},
	{{'i', mode::game }, &GameSession::inventory_init},
	{{'t', mode::game }, &GameSession::take_init},
	{{'l', mode::game }, &GameSession::loot_init},
	{{'a', mode::game }, &GameSession::attack_init},
	{{'n', mode::game }, &GameSession::next_turn},

	{{27, mode::inventory }, &GameSession::close},
	{{'i', mode::inventory }, &GameSession::close},
	{{'d', mode::inventory }, &GameSession::inventory_drop},
	{{13, mode::inventory }, &GameSession::inventory_activate},
	{{72, mode::inventory }, &GameSession::table_choose_up},
	{{80, mode::inventory }, &GameSession::table_choose_down},

	{{27, mode::attack }, &GameSession::close},
	{{'a', mode::attack }, &GameSession::close},
	{{13, mode::attack }, &GameSession::attack_activate},
	{{80, mode::attack }, &GameSession::attack_cursor_up},
	{{72, mode::attack }, &GameSession::attack_cursor_down},
	{{75, mode::attack }, &GameSession::attack_cursor_left},
	{{77, mode::attack }, &GameSession::attack_cursor_right},

	{{27, mode::take }, &GameSession::close},
	{{'t', mode::take }, &GameSession::close},
	{{72, mode::take }, &GameSession::table_choose_up},
	{{80, mode::take }, &GameSession::table_choose_down},
	{{13, mode::take }, &GameSession::take_activate},

	{{27, mode::loot }, &GameSession::close},
	{{'l', mode::loot }, &GameSession::close},
	{{72, mode::loot }, &GameSession::table_choose_up},
	{{80, mode::loot }, &GameSession::table_choose_down},
	{{13, mode::loot }, &GameSession::loot_activate},
};
