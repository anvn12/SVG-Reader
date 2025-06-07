#ifndef General_h
#define General_h
#pragma once

// RGB color
class Color {
private:
	int red, green, blue;
public:
	Color()
		: red(0), green(0), blue(0) {}
	Color(int r, int g, int b)
		: red(r), green(g), blue(b)	{}
};

class Point {
private:
	double x, y;
public:
	Point()
		: x(0), y(0) {}
	Point(double coorX, double coorY)
		: x(coorX), y(coorY) {}
};


#endif
