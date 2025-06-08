#ifndef General_h
#define General_h
#pragma once

// RGB color
class RGBColor {
private:
	int red, green, blue;
public:
	RGBColor()
		: red(0), green(0), blue(0) {}
	RGBColor(int r, int g, int b)
		: red(r), green(g), blue(b)	{}
};

class Point2D {
//private:
public:
	double x, y;
	Point2D()
		: x(0), y(0) {}
	Point2D(double coorX, double coorY)
		: x(coorX), y(coorY) {}
};


#endif
