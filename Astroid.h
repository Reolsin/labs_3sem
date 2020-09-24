#ifndef _ASTROID_H_
#define _ASTROID_H_
#include <math.h>

#define value 1.178097245

namespace Prog2 {

	struct Point {
		double x, y;
		Point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {}
	};

	class Astroid {

	private:
		double R;
		Point C;

	public:
		Astroid(double r = 1);
		Astroid(const Point& P, double r = 1);
		Astroid(double x0, double y0, double r = 1);

		Astroid& setC(const Point& P) { C = P; return *this; };
		Astroid& setR(double r);

		Point getC() const { return C; };
		double getR() const { return R; };

		double length() const { return 6 * R; } //длина всей кривой
		double length(double t) const; //длину от 0 до t
		double curvature_radius(double t) const { return (1.5 * R * sin(2 * t)); };	//радиус кривизны от t
		double area() const { return (value * R * R); };	//площадь
		Point get_xy_from_t(double t) const;	//х и у в зависимости от t
		Point f(double x) const;	//вернуть y в зависимости от х

		char** formuls() const; // формулы
	};
}
#endif
