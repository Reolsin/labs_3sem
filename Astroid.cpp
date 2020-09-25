#include <strstream>

#include <stdio.h>
#include <strstream>

#include "Astroid.h"
#define pi 3.14159265359
#define two_third 0.66666666667

namespace Prog2 {

	Astroid::Astroid(double r) : C(0, 0)
	{
		if (r < 0) throw std::exception("------Error. Invalid radius.");
		R = r;
	}

	Astroid::Astroid(const Point& P, double r) : C(P)
	{
		if (r < 0) throw std::exception("------Error.Invalid radius.");
		R = r;
	}

	Astroid::Astroid(double x0, double y0, double r) : C(x0, y0)
	{
		if (r < 0) throw std::exception("------Error. Invalid radius.");
		R = r;
	}

	Astroid& Astroid::setR(double r)
	{
		if (r < 0) throw std::exception("------Error. Invalid radius.");
		R = r;
		return *this;
	}

	double Astroid::length(double t) const
	{
		int k = (int)2 * t / pi;
		t = sin(t - k * pi / 2);
		return k * 1.5 * R + 1.5 * R * t * (t >= 0 ? t : -t);
	}

	Point Astroid::get_xy_from_t(double t) const
	{
		double sint = sin(t);
		t = cos(t);
		Point p(R * t * t * t + C.x, R * sint * sint * sint + C.y);
		return p;
	}

	Point Astroid::f(double x) const
	{
		double dx = x - C.x;
		dx = dx > 0 ? dx : -dx;
		if (dx > R)
			throw std::exception("------Error. Invalid x.");
		dx = pow(pow(R, two_third) - pow(dx, two_third), 1.5);
		Point res;
		res.x = C.y + dx;
		res.y = C.y - dx;
		return res;
	}

	char** Astroid::formuls() const
	{
		const char* s1 = "(x - )^(2/3) + (y - )^(2/3) = ";
		const char* s2 = "x = *sin(t)^3 + , y = *cos(t)^3 + ";
		int l = strlen(s2) + 1;
		char num[20];
		sprintf_s(num, 20, "%.2f", C.x);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", C.y);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", R);
		l += 2 * strlen(num);
		char** s = new char* [2];
		s[0] = new char[l];
		s[1] = new char[l];
		if (C.x == 0) {
			sprintf_s(s[0], l, "x^(2/3)"); sprintf_s(s[1], l, "x = %.2f*cos(t)^3, y = ", R);
		}
		else if (C.x > 0) {
			sprintf_s(s[0], l, "(x - %.2f)^(2/3)", C.x); sprintf_s(s[1], l, "x = %.2f*cos(t)^3 + %.2f, y = ", R, C.x);
		}
		else {
			sprintf_s(s[0], l, "(x + %.2f)^(2/3)", -C.x); sprintf_s(s[1], l, "x = %.2f*cos(t)^3 - %.2f, y = ", R, -C.x);
		}
		int k1 = strlen(s[0]);
		int k2 = strlen(s[1]);
		if (C.y == 0) {
			sprintf_s(s[0] + k1, l - k1, " + y^(2/3) = %.2f", R); sprintf_s(s[1] + k2, l - k2, "%.2f*sin(t)^3", R);
		}
		else if (C.y > 0) {
			sprintf_s(s[0] + k1, l - k1, " + (y - %.2f)^(2/3) = %.2f", C.y, R); sprintf_s(s[1] + k2, l - k2, "%.2f*sin(t)^3 + %.2f", R, C.y);
		}
		else {
			sprintf_s(s[0] + k1, l - k1, " + (y + %.2f)^(2/3) = %.2f", -C.y, pow(R, two_third)); sprintf_s(s[1] + k2, l - k2, "%.2f*sin(t)^3 - %.2f", R, -C.y);
		}
		return s;
	}
}
