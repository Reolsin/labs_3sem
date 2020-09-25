#include "pch.h"
#include "../Lib/Astroid.h"

TEST(Constructor, DefaultConstructor)
{
	Prog2::Astroid a1;
	ASSERT_EQ(0, a1.getC().x);
	ASSERT_EQ(0, a1.getC().y);
	ASSERT_EQ(1, a1.getR());
}

TEST(Constructor, InitConstructor)
{
	Prog2::Point p(2, 4);

	Prog2::Astroid a1(5);
	ASSERT_EQ(0, a1.getC().x);
	ASSERT_EQ(0, a1.getC().y);
	ASSERT_EQ(5, a1.getR());

	Prog2::Astroid a2(1, 2, 3);
	ASSERT_EQ(1, a2.getC().x);
	ASSERT_EQ(2, a2.getC().y);
	ASSERT_EQ(3, a2.getR());

	Prog2::Astroid a3(p, 4);
	ASSERT_EQ(2, a3.getC().x);
	ASSERT_EQ(4, a3.getC().y);
	ASSERT_EQ(4, a3.getR());
	p.x = 5;
	ASSERT_EQ(2, a3.getC().x);
	ASSERT_EQ(4, a3.getC().y);
	ASSERT_EQ(4, a3.getR());
}

TEST(Constructor, TestException)
{
	Prog2::Point p;
	ASSERT_ANY_THROW(Prog2::Astroid(2, 5, -5));
	ASSERT_ANY_THROW(Prog2::Astroid(p, -1));
}

TEST(Methods, Setters)
{
	Prog2::Astroid a;
	Prog2::Point p1(3, 2);
	a.setC(p1);
	ASSERT_EQ(3, a.getC().x);
	ASSERT_EQ(2, a.getC().y);

	Prog2::Point p2(-3, -2);
	a.setC(p2);
	ASSERT_EQ(-3, a.getC().x);
	ASSERT_EQ(-2, a.getC().y);

	a.setR(2);
	ASSERT_EQ(2, a.getR());
	ASSERT_ANY_THROW(a.setR(-1));
}

TEST(Methods, Default)
{
	Prog2::Astroid a1;
	const double PI = 3.14159, err = 0.00001;
	ASSERT_NEAR(PI*3/8, a1.area(), err);
	ASSERT_NEAR(6, a1.length(), err);
	ASSERT_NEAR(1.0621101274103568, a1.length(1), err);

	ASSERT_EQ(0, a1.f(1).x);
	ASSERT_EQ(0, a1.f(1).y);
	ASSERT_EQ(1, a1.f(0).x);
	ASSERT_EQ(-1, a1.f(0).y);
	ASSERT_ANY_THROW(a1.f(2));
	
	ASSERT_NEAR(0, a1.curvature_radius(PI/2), err);
	ASSERT_NEAR(1.5, a1.curvature_radius(PI/4), err);

	ASSERT_STREQ("x^(2/3) + y^(2/3) = 1.00", a1.formuls()[0]);
	ASSERT_STREQ("x = 1.00*cos(t)^3, y = 1.00*sin(t)^3", a1.formuls()[1]);
}

TEST(Methods, Parameters)
{
	Prog2::Astroid a2(1, -3, 2);
	const double PI = 3.14159, err = 0.00001;
	ASSERT_NEAR(PI * 3 / 2, a2.area(), err);

	ASSERT_NEAR(12, a2.length(), err);
	ASSERT_NEAR(3, a2.length(PI / 2), err);
	ASSERT_NEAR(-18, a2.length(-3 * PI), err);
	ASSERT_NEAR(2.1242202548207136, a2.length(1), err);

	ASSERT_EQ(-3, a2.f(3).x);
	ASSERT_EQ(-3, a2.f(3).y);
	ASSERT_NEAR(-2.5498035356254345, a2.f(0).x, err);
	ASSERT_NEAR(-3.4501964643745655, a2.f(0).y, err);
	ASSERT_ANY_THROW(a2.f(-2));

	ASSERT_EQ(3, a2.get_xy_from_t(0).x);
	ASSERT_EQ(-3, a2.get_xy_from_t(0).y);
	ASSERT_NEAR(1, a2.get_xy_from_t(PI * 7 / 2).x, err);
	ASSERT_NEAR(-5, a2.get_xy_from_t(PI * 7 / 2).y, err);
	ASSERT_NEAR(1.31545721050198694, a2.get_xy_from_t(1).x, err);
	ASSERT_NEAR(-1.8083535268180888, a2.get_xy_from_t(1).y, err);

	ASSERT_NEAR(3, a2.curvature_radius(PI / 4), err);
	ASSERT_NEAR(1.5 * sqrt(2), a2.curvature_radius(-PI / 8), err);

	ASSERT_STREQ("(x - 1.00)^(2/3) + (y + 3.00)^(2/3) = 1.59", a2.formuls()[0]);
	ASSERT_STREQ("x = 2.00*cos(t)^3 + 1.00, y = 2.00*sin(t)^3 - 3.00", a2.formuls()[1]);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
