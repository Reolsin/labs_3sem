#pragma once
#include "classes.h"
#include "Units.h"

namespace Gamma {

	struct Cell {
		std::vector<Item*> Items;
		char cell_type;

		Cell() : cell_type('.') {}

		bool add_item(Item*);
		Item* pick_up(int);
	};

	struct GameLevel {
		std::vector<std::vector<Cell>> Map;
		int h, l;

		GameLevel();
		GameLevel(std::ifstream&);

		std::vector<Item*>& get_items(const Point& p);
		bool add_item(Item*, int, int);
		bool add_item(Item* item, const Point& p);
		Item* pick_up(int, int, int);
		Item* pick_up(const Point&, int);
		bool point_access(const Point&);
	};

	enum mode { gamemode, inventorymode, attackmode, takemode };
	struct operation_code {
		int code;
		mode m;
	};
	struct CompareType {
		using is_transparent = std::true_type;
		bool operator()(const operation_code& lhs, const operation_code& rhs) const 
		{ return (lhs.code < rhs.code) || ((lhs.code == rhs.code) && (lhs.m < rhs.m)); }
	};

	class GameSession {
	private:
		static std::map<operation_code, bool (Gamma::GameSession::*)(), CompareType> operation;

		int current_unit;
		Point attack_cursor;
		std::vector<Operative*> player;
		std::vector<Unit*> enemy;

		GameLevel level;

		std::string message;
		mode current_mode;
		
		void move(const Point&);
		bool move_up();
		bool move_down();
		bool move_right();
		bool move_left();
		bool choose_next();
		bool choose_previous();

		bool inventory_init();
		bool inventory_drop();
		bool inventory_activate();
		bool inventory_left();
		bool inventory_right();

		bool take_init();
		bool take_activate();
		bool take_choose_left();
		bool take_choose_right();

		bool attack_init();
		bool attack_activate();
		bool attack_cursor_up();
		bool attack_cursor_down();
		bool attack_cursor_right();
		bool attack_cursor_left();

		bool close();
		bool next_turn();
		bool exit();

		bool not_unit_here(const Point&);
	public:
		GameSession() : current_unit(0), attack_cursor(), current_mode(gamemode) {}
		GameSession(std::ifstream&) : current_unit(0), current_mode(gamemode) {}
		~GameSession() {}

		bool execute(int button)
		{
			if (operation.count({ button, current_mode }) == 1)
				return (this->*operation.at({ button, current_mode }))();
			return true;
		}
		bool check();

		void draw() {}

		bool save(std::ofstream);
	};
}
