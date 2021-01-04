#include "pch.h"
#include <sstream>
#include "../Operatives_vs_Aliens/Session.h"

namespace Gamma {

	TEST(My_vector, Constructors) {
		My_vector<std::string> m_v1;
		EXPECT_EQ(m_v1.size(), 0);
		EXPECT_EQ(m_v1.is_full(), true);
		EXPECT_EQ(m_v1.not_empty(), false);
		EXPECT_EQ(m_v1.capacity(), 0);

		My_vector<std::string> m_v2(9, "ex1");
		EXPECT_EQ(m_v2.size(), 9);
		EXPECT_EQ(m_v2.is_full(), false);
		EXPECT_EQ(m_v2.not_empty(), true);
		EXPECT_EQ(m_v2.capacity(), 10);
		EXPECT_STREQ(m_v2[0].c_str(), "ex1");

		My_vector<std::string> m_v3(10, "ex2");
		EXPECT_EQ(m_v3.size(), 10);
		EXPECT_EQ(m_v3.is_full(), false);
		EXPECT_EQ(m_v3.not_empty(), true);
		EXPECT_EQ(m_v3.capacity(), 15);
		EXPECT_STREQ(m_v3[0].c_str(), "ex2");

		My_vector<std::string> m_v4(m_v3);
		EXPECT_EQ(m_v4.size(), 10);
		EXPECT_EQ(m_v4.is_full(), false);
		EXPECT_EQ(m_v4.not_empty(), true);
		EXPECT_EQ(m_v4.capacity(), 15);
		EXPECT_STREQ(m_v4[0].c_str(), "ex2");

		My_vector<std::string> m_v5(My_vector<std::string>(9, "ex5"));
		EXPECT_EQ(m_v5.size(), 9);
		EXPECT_EQ(m_v5.is_full(), false);
		EXPECT_EQ(m_v5.not_empty(), true);
		EXPECT_EQ(m_v5.capacity(), 10);
		EXPECT_STREQ(m_v5[0].c_str(), "ex5");
	}

	TEST(My_vector, Operators) {
		My_vector<std::string> m_v1;
		My_vector<std::string> m_v2(9, "ex1");
		m_v1 = m_v2;
		EXPECT_EQ(m_v1.size(), 9);
		EXPECT_EQ(m_v1.is_full(), false);
		EXPECT_EQ(m_v1.not_empty(), true);
		EXPECT_EQ(m_v1.capacity(), 10);
		EXPECT_STREQ(m_v1[0].c_str(), "ex1");

		m_v1 = My_vector<std::string>(10, "ex2");
		EXPECT_EQ(m_v1.size(), 10);
		EXPECT_EQ(m_v1.is_full(), false);
		EXPECT_EQ(m_v1.not_empty(), true);
		EXPECT_EQ(m_v1.capacity(), 15);
		EXPECT_STREQ(m_v1[0].c_str(), "ex2");

		m_v1[0] = "ex";
		EXPECT_STREQ(m_v1[0].c_str(), "ex");
	}

	TEST(My_vector, Methods) {
		My_vector<std::string> m_v1;
		m_v1.resize(5);
		EXPECT_EQ(m_v1.size(), 5);
		EXPECT_EQ(m_v1.is_full(), false);
		EXPECT_EQ(m_v1.not_empty(), true);
		EXPECT_EQ(m_v1.capacity(), 10);
		EXPECT_STREQ(m_v1[0].c_str(), "");

		EXPECT_ANY_THROW(m_v1.at(-1));
		EXPECT_ANY_THROW(m_v1.at(5));

		m_v1.push_back("1");
		EXPECT_STREQ(m_v1[5].c_str(), "1");
		m_v1.push_back("2");
		m_v1.push_back("3");
		m_v1.push_back("4");
		m_v1.push_back("5");
		EXPECT_EQ(m_v1.capacity(), 10);
		m_v1.push_back("6");
		EXPECT_EQ(m_v1.capacity(), 15);
		EXPECT_STREQ(m_v1.back().c_str(), "6");

		for (int i = 0; i < 9; i++)
			m_v1.pop_back();
		EXPECT_EQ(m_v1.size(), 2);
		EXPECT_EQ(m_v1.capacity(), 5);

		m_v1.clear();
		EXPECT_EQ(m_v1.size(), 0);
		EXPECT_EQ(m_v1.is_full(), true);
		EXPECT_EQ(m_v1.not_empty(), false);
		EXPECT_EQ(m_v1.capacity(), 0);
	}

	TEST(My_vectorIt, Constructors_and_Methods) {
		My_vector<std::string> m_v(6, std::string());

		My_vect::My_vectorIt<std::string> example1;
		int* p = reinterpret_cast<int*>(&(*example1));
		EXPECT_EQ(p, nullptr);

		My_vect::My_vectorIt<std::string> example2(&m_v[0]);

		int n = 1;
		for (auto i = m_v.begin(); i != m_v.end(); i++, n++)
			*i = std::to_string(n) + ".str";
		EXPECT_STREQ(m_v[0].c_str(), "1.str");
		EXPECT_STREQ(m_v[1].c_str(), "2.str");
		EXPECT_STREQ(m_v[2].c_str(), "3.str");
		EXPECT_STREQ(m_v[3].c_str(), "4.str");
		EXPECT_STREQ(m_v[4].c_str(), "5.str");
		EXPECT_STREQ(m_v[5].c_str(), "6.str");

		n = 2;
		for (std::string& i : m_v)
			i = std::to_string(++n) + ".str";
		EXPECT_STREQ(m_v[0].c_str(), "3.str");
		EXPECT_STREQ(m_v[1].c_str(), "4.str");
		EXPECT_STREQ(m_v[2].c_str(), "5.str");
		EXPECT_STREQ(m_v[3].c_str(), "6.str");
		EXPECT_STREQ(m_v[4].c_str(), "7.str");
		EXPECT_STREQ(m_v[5].c_str(), "8.str");

		EXPECT_STREQ(example2->c_str(), "3.str");
		EXPECT_STREQ((*++example2).c_str(), "4.str");
		EXPECT_STREQ((*example2++).c_str(), "4.str");
		EXPECT_STREQ(example2->c_str(), "5.str");
	}

	TEST(Items, file_constructors_and_getters) {
		std::istringstream ss("aidkit 20 30 2 2 70 sniper_rifle 20 20 10 10 30 20 1.1 sniper_ammo 20 15 50 50 1.1");
		aidkit ak((std::ifstream&)ss);
		weapon g((std::ifstream&)ss);
		ammunition ammo((std::ifstream&)ss);
		EXPECT_EQ(ak.up(), 30);
		EXPECT_EQ(ak.w(), 20);
		EXPECT_EQ(g.up(), 20);
		EXPECT_EQ(g.w(), 20);
		EXPECT_EQ(ammo.up(), 15);
		EXPECT_EQ(ammo.w(), 20);
	}

	TEST(Units, file_constructors_and_getters) {
		std::istringstream ss("Operative A 1 2 100 100 100 100 10 0 1 weapon sniper_rifle 20 20 10 10 30 20 1.1 100 2 aidkit aidkit 20 30 2 2 70 ammunition sniper_ammo 20 15 50 50 1.1 Alien_range R 5 2 100 100 100 100 5 5 1.1 - Alien_friendly E 5 1 100 100 100 100 5 5 100 4 - - - - Alien_melee F 6 1 100 100 100 100 5 5 1.1 weapon fist 20 20 10 10 30 20 1.1");
		Operative op((std::ifstream&)ss);
		Alien_range a_r((std::ifstream&)ss);
		Alien_friendly a_f((std::ifstream&)ss);
		Alien_melee a_m((std::ifstream&)ss);

		EXPECT_EQ(op.vision(), 10);
		EXPECT_EQ(op.pos().x, 1);
		EXPECT_EQ(op.pos().y, 2);
		EXPECT_EQ(op.check_MP(100), true);
		EXPECT_EQ(op.check_MP(101), false);
		EXPECT_EQ(op.avatar(), 'A');
		EXPECT_STREQ(op.name_().c_str(), "Operative");
		EXPECT_EQ(op.is_alive(), true);

		EXPECT_EQ(a_r.vision(), 5);
		EXPECT_EQ(a_r.pos().x, 5);
		EXPECT_EQ(a_r.pos().y, 2);
		EXPECT_EQ(a_r.check_MP(100), true);
		EXPECT_EQ(a_r.check_MP(101), false);
		EXPECT_EQ(a_r.avatar(), 'R');
		ASSERT_STREQ(a_r.name_().c_str(), "Alien_range");
		EXPECT_EQ(a_r.is_alive(), true);

		EXPECT_EQ(a_f.vision(), 5);
		EXPECT_EQ(a_f.pos().x, 5);
		EXPECT_EQ(a_f.pos().y, 1);
		EXPECT_EQ(a_f.check_MP(100), true);
		EXPECT_EQ(a_f.check_MP(101), false);
		EXPECT_EQ(a_f.avatar(), 'E');
		EXPECT_STREQ(a_f.name_().c_str(), "Alien_friendly");
		EXPECT_EQ(a_f.is_alive(), true);

		EXPECT_EQ(a_m.vision(), 5);
		EXPECT_EQ(a_m.pos().x, 6);
		EXPECT_EQ(a_m.pos().y, 1);
		EXPECT_EQ(a_m.check_MP(100), true);
		EXPECT_EQ(a_m.check_MP(101), false);
		EXPECT_EQ(a_m.avatar(), 'F');
		EXPECT_STREQ(a_m.name_().c_str(), "Alien_melee");
		EXPECT_EQ(a_m.is_alive(), true);
	}

	TEST(Cell_, setter) {
		Cell c;
		EXPECT_EQ(c.Items.size(), 0);
		c.add_item(new ammunition());
		EXPECT_EQ(c.Items.size(), 1);
	}

	TEST(Level, file_constructors_and_getters) {
		std::istringstream ss("5 5 .#|.- ..... ..... ..... ..... 2 0 0 ammunition pistol_ammo 20 15 71 100 0.9 0 0 aidkit aidkit 20 30 2 2 70 ");
		GameLevel lvl((std::ifstream&)ss);

		EXPECT_EQ(lvl.point_access(0, 0), true);
		EXPECT_EQ(lvl.point_access(0, 1), false);
		EXPECT_EQ(lvl.is_transparent(0, 0), true);
		EXPECT_EQ(lvl.is_transparent(0, 1), false);
		EXPECT_EQ(lvl.is_transparent(0, 2), true);
		EXPECT_EQ(lvl.is_transparent(0, 3), true);
		EXPECT_EQ(lvl.is_transparent(0, 4), true);
		EXPECT_EQ(lvl.get_items(Point(0, 0))->size(), 2);
		EXPECT_EQ(lvl.get_items(Point(2, 0))->size(), 0);
		EXPECT_EQ(lvl.point_on_map(5, 4), false);
		EXPECT_EQ(lvl.point_on_map(4, 4), true);
		EXPECT_EQ(lvl[Point(0, 0)].cell_type, '?');
		EXPECT_EQ(lvl[Point(0, 0)].Items.size(), 2);
		EXPECT_EQ(lvl[Point(1, 0)].cell_type, '#');
		EXPECT_EQ(lvl[Point(3, 0)].Items.size(), 0);
	}

	TEST(Session, file_constructors_and_getters) {
		std::istringstream ss("5 5 ..... ..... ..... ..... ..... 2 0 0 ammunition pistol_ammo 20 15 71 100 0.9 0 0 aidkit aidkit 20 30 2 2 70 2 ally Alien_range Alien_range R 1 1 100 100 100 100 5 5 1.1 - enemy Alien_melee Alien_melee F 0 0 100 100 100 100 5 5 1.1 weapon fist 20 20 10 10 30 20 1.1 ");
		GameSession Session((std::ifstream&)ss);

		EXPECT_EQ(Session.check(), true);
		int* p = (int*)Session.alive_unit_here(Point(0, 0));
		EXPECT_NE(p, nullptr);
		int n = Session.dead_units_here(Point(0, 0)).size();
		EXPECT_EQ(n, 0);
		p = (int*)Session.alive_unit_here(Point(1, 0));
		EXPECT_EQ(p, nullptr);
		p = (int*)Session.alive_unit_here(Point(1, 1));
		EXPECT_EQ(p, nullptr);
	}

	TEST(Units_Items, setters_and_use) {
		std::istringstream ss_units("Operative A 1 2 100 100 100 100 10 0 1 weapon sniper_rifle 20 20 10 10 30 20 1.1 100 2 aidkit aidkit 20 30 2 2 70 ammunition sniper_ammo 20 15 50 50 1.1");
		Operative* op = new Operative((std::ifstream&)ss_units);

		std::istringstream ss_items("aidkit 20 30 2 2 70 sniper_rifle 20 20 10 10 30 20 1.1 sniper_ammo 20 15 50 50 1.1");
		aidkit ak((std::ifstream&)ss_items);
		weapon g((std::ifstream&)ss_items);
		ammunition ammo((std::ifstream&)ss_items);

		EXPECT_STREQ(ak.use(op)->c_str(), "Unit has full HP.");
		EXPECT_STREQ(g.use(op)->c_str(), "Success.");
		EXPECT_STREQ(ammo.use(op)->c_str(), "Weapon has full clip or wrong ammo type.");
		
		EXPECT_STREQ(op->use_item(0)->c_str(), "Unit has full HP.");
		EXPECT_STREQ(op->use_item(1)->c_str(), "Weapon has full clip or wrong ammo type.");
	}

	TEST(Level, setters) {
		std::istringstream ss("5 5 .#|.- ..... ..... ..... ..... 2 0 0 ammunition pistol_ammo 20 15 71 100 0.9 0 0 aidkit aidkit 20 30 2 2 70 ");
		GameLevel lvl((std::ifstream&)ss);

		std::istringstream ss_items("aidkit 20 30 2 2 70 sniper_rifle 20 20 10 10 30 20 1.1 sniper_ammo 20 15 50 50 1.1");
		aidkit* ak = new aidkit((std::ifstream&)ss_items);
		weapon* g = new weapon((std::ifstream&)ss_items);
		ammunition* ammo = new ammunition((std::ifstream&)ss_items);

		EXPECT_EQ(lvl.get_items(Point(0, 1))->size(), 0);
		EXPECT_EQ(lvl.add_item(ak, 0, 1), true);
		EXPECT_EQ(lvl.get_items(Point(0, 1))->size(), 1);
		EXPECT_EQ(lvl.add_item(ak, 0, -1), false);
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
