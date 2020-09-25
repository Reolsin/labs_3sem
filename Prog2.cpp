#include <iostream>
#include "../Lib/Astroid.h"
#define pi 3.14159265359

int main(int argc, char* argv[])
{
	Prog2::Astroid curve(2, 1, 2);
	Prog2::Point p(3);
	int fl1 = 1;
	double r;
	char** s;
	while (fl1) {
		s = curve.formuls();
		std::cout << "Astrioid formuls:\nXY coordinate system: " << s[0] << ";\nParametric form: " << s[1] << std::endl;
		delete[] s[0]; delete[] s[1];
		std::cout << "getC: " << curve.getC().x << curve.getC().y << std::endl;
		std::cout << "getR: " << curve.getR() << std::endl;
		std::cout << "area: " << curve.area() << std::endl;
		std::cout << "perimeter: " << curve.length() << std::endl;
		std::cout << "Length to the t = 2*pi: " << curve.length(2 * pi) << std::endl;
		std::cout << "Length to the t = pi/2: " << curve.length(pi / 2) << std::endl;
		std::cout << "Length to the t = -pi: " << curve.length(-pi) << std::endl;
		std::cout << "Curvature radius to the t = 2*pi: " << curve.curvature_radius(pi / 2) << std::endl;
		std::cout << "Curvature radius to the t = pi/2: " << curve.curvature_radius(7 * pi) << std::endl;
		std::cout << "Curvature radius to the t = -pi: " << curve.curvature_radius(-1) << std::endl;
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter x for calculate value y(x) or precc ctrl+Z to quit:" << std::endl;
			double x;
			Prog2::Point y;
			std::cin >> x;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				y = curve.f(x);
				std::cout << "y1 = " << y.x << ", y2 = " << y.y << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		std::cout << "Enter new x, y and r to continue or press ctrl+Z to quit:" << std::endl;
		std::cin >> p.x >> p.y >> r;
		fl1 = std::cin.good();
		if (!fl1)
			continue;
		curve.setC(p);
		try {
			curve.setR(r);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	return 0;
}
