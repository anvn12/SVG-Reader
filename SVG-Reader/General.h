#ifndef General_h
#define General_h
#pragma once

#include <vector>
#include <sstream>

// RGB color
class RGBColor {
private:
	int red, green, blue;

	int clamp(int value) const;

public:
	RGBColor()
		: red(0), green(0), blue(0) {}

	RGBColor(int r, int g, int b)
		: red(clamp(r)), green(clamp(g)), blue(clamp(b)) {}

	RGBColor getColor() { return *this; }

	int getRed() const { return red; }
	int getGreen() const { return green; }
	int getBlue() const { return blue; }

	void setRed(int r) { red = clamp(r); }
	void setGreen(int g) { green = clamp(g); }
	void setBlue(int b) { blue = clamp(b); }
};

class Point2D {
private:
	int x, y;

public:
	Point2D()
		: x(0), y(0) {}

	Point2D(int coorX, int coorY)
		: x(coorX), y(coorY) {}

	int getX() const { return x; }
	int getY() const { return y; }
	
	void setX(int value) { x = value; }
	void setY(int value) { y = value; }
};


// extract char* to RGBColor
RGBColor textToRGB(char*);


//help for reading poly points
vector<PointF> parsePoints(const string& pointsStr);

#endif
