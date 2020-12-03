#include "Session.h"

using namespace Gamma;

bool Cell::add_item(Item* item)
{
	if (cell_type == '.' || cell_type == '?') {
		cell_type = '?';
		Items.push_back(item);
		return true;
	}
	return false;
}

Item* Cell::pick_up(int i)
{
	if (Items.size() > i && i >= 0)
	{
		Item* item = Items[i];
		std::swap(Items[i], Items.back());
		Items.pop_back();
		if (Items.size() == 0)
			cell_type = '.';
		return item;
	}
	return nullptr;
}


GameLevel::GameLevel()
{
	std::ifstream s("default.txt");
	s >> h >> l;
	s.ignore(1);
	for (int i = 0; i < h; i++) {
		Map[i].resize(l);
		for (int j = 0; j < l; j++)
			s >> Map[i][j].cell_type;
		s.ignore(1);
	}
}

GameLevel::GameLevel(std::ifstream& s)
{
	s >> h >> l;
	s.ignore(1);
	for (int i = 0; i < h; i++) {
		Map[i].resize(l);
		for (int j = 0; j < l; j++)
			s >> Map[i][j].cell_type;
		s.ignore(1);
	}
}

std::vector<Item*>& GameLevel::get_items(const Point& p)
{
	return Map[p.x][p.y].Items;
}

bool GameLevel::add_item(Item* item, int x, int y)
{ 
	if (x >= 0 && x < l)
		if (y >= 0 && y < h)
			return Map[x][y].add_item(item);
	return false;
}

bool GameLevel::add_item(Item* item, const Point& p) { return add_item(item, p.x, p.y); }

Item* GameLevel::pick_up(int x, int y, int i)
{
	if (x >= 0 && x < l)
		if (y >= 0 && y < h)
			return Map[x][y].pick_up(i);
	return nullptr;
}

Item* GameLevel::pick_up(const Point& p, int i) { return pick_up(p.x, p.y, i); }

bool GameLevel::point_access(const Point& p)
{
	return ((l > p.x) && (0 <= p.x) && (h > p.y) && (0 <= p.y) && Map[p.x][p.y].cell_type == '.');
}


GameSession::GameSession()
{

}

void GameSession::move(const Point& next_position)
{
	if (level.point_access(next_position))
		if (not_unit_here(next_position))
			if(player[current_unit]->move(next_position));
}

bool GameSession::move_up()
{
	move(player[current_unit]->get_pos() += (0, 1));
	return true;
}
bool GameSession::move_down()
{
	move(player[current_unit]->get_pos() += (0, -1));
	return true;
}
bool GameSession::move_right() 
{ 
	move(player[current_unit]->get_pos() += (1, 0));
	return true; 
}
bool GameSession::move_left() 
{ 
	move(player[current_unit]->get_pos() += (-1, 0));
	return true; 
}

bool GameSession::choose_next() 
{
	current_unit = (current_unit + 1) % player.size(); 
	return true;
}

bool GameSession::choose_previous() 
{ 
	current_unit = (player.size() + current_unit - 1) % player.size(); 
	return true; 
}

bool GameSession::inventory_init()
{
	if (player[current_unit]->is_alive()) {
		current_mode = inventorymode;
	}
	return true;
}

bool GameSession::take_init()
{
	if (level.get_items(player[current_unit]->get_pos()).size() > 0) {
		current_mode = takemode;
	}
	return true;
}

bool GameSession::attack_init()
{
	current_mode = attackmode;
	return true;
}

bool GameSession::close()
{
	current_mode = gamemode;
	return true;
}

bool GameSession::exit()
{
	return false;
}

bool GameSession::check()
{
	bool status = true;
	for (int i = 0; i < player.size(); i++)
		status = status && player[i]->is_alive();
	for (int i = 0; i < enemy.size(); i++)
		status = status && enemy[i]->is_alive();
	return status;
}

std::map<operation_code, bool (GameSession::*)(), CompareType> GameSession::operation{
	{{27, gamemode }, &GameSession::exit},
	{{73, gamemode }, &GameSession::choose_next},
	{{81, gamemode }, &GameSession::choose_previous},
	{{72, gamemode }, &GameSession::move_up},
	{{80, gamemode }, &GameSession::move_down},
	{{75, gamemode }, &GameSession::move_left},
	{{77, gamemode }, &GameSession::move_right},
	{{'i', gamemode }, &GameSession::inventory_init},
	{{'t', gamemode }, &GameSession::take_init},
	{{'a', gamemode }, &GameSession::attack_init},
	{{'n', gamemode }, &GameSession::next_turn},

	{{27, inventorymode }, &GameSession::close},
	{{'i', inventorymode }, &GameSession::close},
	{{'d', inventorymode }, &GameSession::inventory_drop},
	{{13, inventorymode }, &GameSession::inventory_activate},
	{{75, inventorymode }, &GameSession::inventory_left},
	{{77, inventorymode }, &GameSession::inventory_right},

	{{27, attackmode }, &GameSession::close},
	{{'a', attackmode }, &GameSession::close},
	{{13, attackmode }, &GameSession::attack_activate},
	{{72, attackmode }, &GameSession::attack_cursor_up},
	{{80, attackmode }, &GameSession::attack_cursor_down},
	{{75, attackmode }, &GameSession::attack_cursor_left},
	{{77, attackmode }, &GameSession::attack_cursor_right},

	{{27, takemode }, &GameSession::close},
	{{'t', takemode }, &GameSession::close},
	{{75, takemode }, &GameSession::take_choose_left},
	{{77, takemode }, &GameSession::take_choose_right},
	{{13, takemode }, &GameSession::take_activate},
};
